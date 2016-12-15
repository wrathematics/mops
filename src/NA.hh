#ifndef MOPS_NA_HH_
#define MOPS_NA_HH_

#include <math.h>
#include <stdint.h>

static inline bool check_na(double val)
{
  // Assumes your compiler supports IEEE 754. If it doesn't, never use your "computer" for numerics.
  return isnan(val);
}

static inline bool check_na(int val)
{
  return val == INT32_MIN;
}


#endif
