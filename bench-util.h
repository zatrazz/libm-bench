/* Benchmark utility functions.
   Copyright (C) 2015-2018 Free Software Foundation, Inc.
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


#ifndef START_ITER
# define START_ITER (100000000)
#endif

/* bench_start reduces the random variations due to frequency scaling by
   executing a small loop with many memory accesses.  START_ITER controls
   the number of iterations.  */

void bench_start (void);

static inline void *
_xmalloc (size_t len, const char *func, int line)
{
  void *ret = malloc (len);
  if (ret == 0)
    {
      fprintf (stderr, "%s:%i: error: failed to allocate %zu bytes\n",
	       func, line, len);
      exit (EXIT_FAILURE);
    }
  return ret;
}
#define xmalloc(len) _xmalloc ((len), __func__, __LINE__)
