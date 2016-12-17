#ifndef MOPS_NA_HH_
#define MOPS_NA_HH_

#include <math.h>

// #include <stdint.h>
// #ifndef INT32_MIN
// #define   INT32_MAX   0x7fffffffL 
// #define   INT32_MIN   (-INT32_MAX - 1L)
// #endif
#include <Rinternals.h>

static inline void set_na(double *val)
{
  *val = NA_REAL;
}

static inline void set_na(int *val)
{
  *val = NA_INTEGER;
}


static inline bool check_na(double val)
{
  // Assumes your compiler supports IEEE 754. If it doesn't, never use your "computer" for numerics.
  return isnan(val);
}

static inline bool check_na(int val)
{
  return val == NA_INTEGER;
}


#endif
