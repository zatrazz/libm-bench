enum {
  RECIPROCAL_THROUGHPUT = 0,
  LATENCY = 1,
  MAX_THROUGHPUT = 2,
  MIN_THROUGHPUT = 3,
  METRICS_LEN = 4
};

struct statistic_t {
  const char *name;
  double *metrics[METRICS_LEN];
};

static const char *metric_name[] =
{
  "reciprocal-throughput",
  "latency",
  "max-throughput",
  "min-throughput"
};

static struct statistic_t *
statistic_alloc (unsigned int iterations)
{
  struct statistic_t *ret = xmalloc (NUM_VARIANTS * sizeof (struct statistic_t));
  for (unsigned int i = 0; i < NUM_VARIANTS; i++)
    {
      ret[i].name = VARIANT (i);
      for (unsigned int j = 0; j < METRICS_LEN; j++)
        ret[i].metrics[j] = xmalloc (iterations * sizeof (double));
    }
  return ret;
}

static void
statistic_free (struct statistic_t *statistics)
{
  for (unsigned int i = 0; i < NUM_VARIANTS; i++)
    for (unsigned int j = 0; j < METRICS_LEN; j++)
      free (statistics[i].metrics[j]);
  free (statistics);
}

static double
statistics_mean (const double *values, size_t len)
{
  if (len == 0)
    return 0.0;

  double acc = 0.0;
  for (size_t i = 0; i < len; i++)
    acc += values[i];
  return acc * (1.0 / len);
}

static double
statistics_median (const double *values, size_t len)
{
  if (len < 3)
    return statistics_mean (values, len);

  return 0.0;
}

static double
statistics_sum_squares (const double *values, size_t len)
{
  double acc = 0.0;
  for (size_t i = 0; i < len; i++)
    acc += values[i] * values[i];
  return acc;
}

static double
statistics_sqrt (const double value)
{
  if (value < 0.0) return 0.0;
  return sqrt (value);
}

static double
statistics_stddev (const double *values, size_t len)
{
  double mean = statistics_mean (values, len);

  if (len == 0)
    return mean;

  /* Sample standard deviation is undefined for n = 1  */
  if (len == 1)
    return 0.0;

  const double avg_squares = statistics_sum_squares (values, len) * (1.0 / len);
  return statistics_sqrt (len / (len - 1.0) * (avg_squares - (mean * mean)));
}

