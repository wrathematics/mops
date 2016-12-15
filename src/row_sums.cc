#include <string.h>

#include "safeomp.h"
#include "mops.h"

#include "NA.hh"


template <typename T>
static inline int row_sums(cbool narm, cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  memset(ret, 0, m*sizeof(*ret));
  
  if (!narm)
  {
    for (int j=0; j<n; j++)
    {
      SAFE_FOR_SIMD
      for (int i=0; i<m; i++)
        ret[i] += x[i + m*j];
    }
  }
  else
  {
    for (int j=0; j<n; j++)
    {
      SAFE_FOR_SIMD
      for (int i=0; i<m; i++)
      {
        if (!check_na(x[i + m*j]))
          ret[i] += x[i + m*j];
      }
    }
  }
  
  return 0;
}



extern "C" int row_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  return row_sums(narm, m, n, x, ret);
}

extern "C" int row_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  return row_sums(narm, m, n, x, ret);
}
