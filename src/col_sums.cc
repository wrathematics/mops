#include "safeomp.h"
#include "mops.h"

#include "NA.hh"

template <typename T>
static inline int col_sums_narm(cint m, cint n, const T*const restrict x, T*const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    SAFE_SIMD
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[j] += x[i + m*j];
    }
  }
  
  return 0;
}

static inline int col_sums_dbl_nonarm(cint m, cint n, const double *const restrict x, double *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    SAFE_SIMD
    for (int i=0; i<m; i++)
      ret[j] += x[i + m*j];
  }
  
  return 0;
}

static inline int col_sums_int_nonarm(cint m, cint n, const int *const restrict x, int *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[j] += x[i + m*j];
      else
      {
        ret[j] = INT32_MIN;
        break;
      }
    }
  }
  
  return 0;
}



extern "C" int col_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return col_sums_narm(m, n, x, ret);
  else
    return col_sums_int_nonarm(m, n, x, ret);
}

extern "C" int col_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return col_sums_narm(m, n, x, ret);
  else
    return col_sums_dbl_nonarm(m, n, x, ret);
}
