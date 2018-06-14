/* Skeleton for benchmark programs.
   Copyright (C) 2013-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>

#include "bench-timing.h"
#include "json-lib.h"
#include "bench-util.h"

#include "bench-util.c"
#include "bench-stat.c"

#define TIMESPEC_AFTER(a, b) \
  (((a).tv_sec == (b).tv_sec) ?						      \
     ((a).tv_nsec > (b).tv_nsec) :					      \
	((a).tv_sec > (b).tv_sec))

#ifndef CLOCK_MONOTONIC_RAW
# define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
#endif

static bool detailed = false;
static unsigned int iterations = 1;
static unsigned int duration = 10;

static unsigned int
parse_uint (const char *str)
{
  char *endptr;
  errno = 0;
  long int ret = strtol (str, &endptr, 10);
  if ((errno == ERANGE && (ret == LONG_MAX || ret == LONG_MIN))
      || (errno != 0 && ret == 0))
    {
      fprintf (stderr, "error: invalid number of iterations (%s)\n", str);
      exit (EXIT_FAILURE);
    }
  return ret;
}

static void
parse_arguments (int argc, char **argv)
{
  int opt;
  while ((opt = getopt (argc, argv, "di:t:")) != -1)
    {
      switch (opt)
	{
	case 'd':
	  detailed = true;
	  break;
	case 'i':
	  iterations = parse_uint (optarg);
	  break;
	case 't':
	  duration = parse_uint (optarg);
	default:
	  {
	    fprintf (stderr, "Usage: %s [-d] [-i iteration]\n",
		     argv[0]);
	    exit (EXIT_FAILURE);
	  }
	}
    }
}

static void
run_iteration (json_ctx_t * json_ctx, int v, unsigned long iters, unsigned long res,
	       double *reciprocal_throughput, double *latency_value,
	       double *max_throughput, double *min_throughput)
{
  struct timespec runtime = { 0 };
  /* Run for approximately DURATION seconds.  */
  clock_gettime (CLOCK_MONOTONIC_RAW, &runtime);
  runtime.tv_sec += duration;

  bool is_bench = strncmp (VARIANT (v), "workload-", 9) == 0;
  double d_total_i = 0;
  timing_t total = 0, max = 0, min = 0x7fffffffffffffff;
  timing_t throughput = 0, latency = 0;
  int64_t c = 0;
  uint64_t cur;
  BENCH_VARS;
  while (1)
    {
      timing_t start, end;
      if (is_bench)
	{
	  /* Benchmark a real trace of calls - all samples are iterated
	     over once before repeating.  This models actual use more
	     accurately than repeating the same sample many times.  */
	  TIMING_NOW (start);
	  for (unsigned int k = 0; k < iters; k++)
	    for (unsigned int i = 0; i < NUM_SAMPLES (v); i++)
	      BENCH_FUNC (v, i);
	  TIMING_NOW (end);
	  TIMING_DIFF (cur, start, end);
	  TIMING_ACCUM (throughput, cur);

	  TIMING_NOW (start);
	  for (unsigned k = 0; k < iters; k++)
	    for (unsigned i = 0; i < NUM_SAMPLES (v); i++)
	      BENCH_FUNC_LAT (v, i);
	  TIMING_NOW (end);
	  TIMING_DIFF (cur, start, end);
	  TIMING_ACCUM (latency, cur);

	  d_total_i += iters * NUM_SAMPLES (v);
	}
      else
	for (unsigned i = 0; i < NUM_SAMPLES (v); i++)
	  {
	    TIMING_NOW (start);
	    for (unsigned k = 0; k < iters; k++)
	      BENCH_FUNC (v, i);
	    TIMING_NOW (end);

	    TIMING_DIFF (cur, start, end);

	    if (cur > max)
	      max = cur;

	    if (cur < min)
	      min = cur;

	    TIMING_ACCUM (total, cur);
	    /* Accumulate timings for the value.  In the end we will divide
	       by the total iterations.  */
	    RESULT_ACCUM (cur, v, i, c * iters, (c + 1) * iters);

	    d_total_i += iters;
	  }
      c++;
      struct timespec curtime;

      memset (&curtime, 0, sizeof (curtime));
      clock_gettime (CLOCK_MONOTONIC_RAW, &curtime);
      if (TIMESPEC_AFTER (curtime, runtime))
	goto done;
    }

  double d_total_s;
  double d_iters;

done:
  d_total_s = total;
  d_iters = iters;

  /* Begin variant.  */
  json_attr_object_begin (json_ctx, VARIANT (v));

  *reciprocal_throughput = throughput / d_total_i;
  *latency_value = latency / d_total_i;
  *max_throughput = d_total_i / throughput * 1000000000.0;
  *min_throughput = d_total_i / latency * 1000000000.0;

  if (is_bench)
    {
      json_attr_double (json_ctx, "reciprocal-throughput",
			*reciprocal_throughput);
      json_attr_double (json_ctx, "latency", *latency_value);
      json_attr_double (json_ctx, "max-throughput", *max_throughput);
      json_attr_double (json_ctx, "min-throughput", *min_throughput);
    }
  else
    {
      json_attr_double (json_ctx, "duration", d_total_s);
      json_attr_double (json_ctx, "iterations", d_total_i);
      json_attr_double (json_ctx, "max", max / d_iters);
      json_attr_double (json_ctx, "min", min / d_iters);
      json_attr_double (json_ctx, "mean", d_total_s / d_total_i);
    }

  if (detailed && !is_bench)
    {
      json_array_begin (json_ctx, "timings");

      for (int i = 0; i < NUM_SAMPLES (v); i++)
	json_element_double (json_ctx, RESULT (v, i));

      json_array_end (json_ctx);
    }

  /* End variant.  */
  json_attr_object_end (json_ctx);
}

int
main (int argc, char **argv)
{
  json_ctx_t json_ctx;

  parse_arguments (argc, argv);

  bench_start ();

  unsigned long iters, res;

#ifdef BENCH_INIT
  BENCH_INIT ();
#endif
  TIMING_INIT (res);

  iters = 1000 * res;

  struct statistic_t *statistics = statistic_alloc (iterations);

  json_init (&json_ctx, 2, stdout);

  /* Begin function.  */
  json_attr_object_begin (&json_ctx, FUNCNAME);

  for (unsigned i = 0; i < iterations; i++)
    {
      char str[128];
      snprintf (str, sizeof (str), "iteration-%d", i);
      json_attr_object_begin (&json_ctx, str);
      for (int v = 0; v < NUM_VARIANTS; v++)
	{
	  run_iteration (&json_ctx, v, iters, res,
			 &statistics[v].metrics[RECIPROCAL_THROUGHPUT][i],
			 &statistics[v].metrics[LATENCY][i],
			 &statistics[v].metrics[MAX_THROUGHPUT][i],
			 &statistics[v].metrics[MIN_THROUGHPUT][i]);
	}
      json_attr_object_end (&json_ctx);
    }

  if (iterations > 1)
    {
      json_attr_object_begin (&json_ctx, "statistics");
      for (int v = 0; v < NUM_VARIANTS; v++)
	{
          json_attr_object_begin (&json_ctx, statistics[v].name);
	  for (int m = 0; m < METRICS_LEN; m++)
	    {
              json_attr_object_begin (&json_ctx, metric_name[m]);
	      json_attr_double (&json_ctx, "mean",
			    statistics_mean(statistics[v].metrics[m], iterations));
	      json_attr_double (&json_ctx, "median",
			    statistics_median(statistics[v].metrics[m], iterations));
	      json_attr_double (&json_ctx, "stddev",
			    statistics_stddev(statistics[v].metrics[m], iterations));
	      json_attr_object_end (&json_ctx);
	    }
	  json_attr_object_end (&json_ctx);
	}

      json_attr_object_end (&json_ctx);
    }

  /* End function.  */
  json_attr_object_end (&json_ctx);

  statistic_free (statistics);

  return 0;
}
