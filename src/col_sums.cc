#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T, typename U>
static inline int col_sums_narm(cint m, cint n, const T *const restrict x, U *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    SAFE_SIMD
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[j] += (U) x[i + m*j];
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

template <typename T>
static inline int col_sums_int_nonarm(cint m, cint n, const int *const restrict x, T *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[j] += (T) x[i + m*j];
      else
      {
        set_na(ret + j);
        break;
      }
    }
  }
  
  return 0;
}

template <typename T>
static inline int col_means_narm(cint m, cint n, const T *const restrict x, double *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    int nobs = m;
    
    SAFE_SIMD
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[j] += (double) x[i + m*j];
      else
        nobs--;
    }
    
    ret[j] /= (double)nobs;
  }
  
  return 0;
}



extern "C" {

int col_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return col_sums_narm(m, n, x, ret);
  else
    return col_sums_int_nonarm(m, n, x, ret);
}

int col_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return col_sums_narm(m, n, x, ret);
  else
    return col_sums_dbl_nonarm(m, n, x, ret);
}

int col_means_int(cbool narm, cint m, cint n, cint *const restrict x, double *const restrict ret)
{
  if (narm)
    return col_means_narm(m, n, x, ret);
  else
  {
    col_sums_int_nonarm(m, n, x, ret);
    return vec_scale(1.0/m, n, ret);
  }
}

int col_means_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return col_means_narm(m, n, x, ret);
  else
  {
    col_sums_dbl_nonarm(m, n, x, ret);
    return vec_scale(1.0/m, n, ret);
  }
}

}
