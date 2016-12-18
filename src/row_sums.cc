#include <stdlib.h>
#include <string.h>

#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T, typename U>
static inline int row_sums_narm(cint m, cint n, const T *const restrict x, U *const restrict ret)
{
  memset(ret, 0, m*sizeof(*ret));
  
  for (int j=0; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[i] += (U) x[i + m*j];
    }
  }
  
  return 0;
}

static inline int row_sums_dbl_nonarm(cint m, cint n, const double *const restrict x, double *const restrict ret)
{
  memset(ret, 0, m*sizeof(*ret));
  
  for (int j=0; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
      ret[i] += x[i + m*j];
  }
  
  return 0;
}

template <typename T>
static inline int row_sums_int_nonarm(cint m, cint n, const int *const restrict x, T *const restrict ret)
{
  memset(ret, 0, m*sizeof(*ret));
  
  for (int j=0; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]) && !check_na(ret[i]))
        ret[i] += (T) x[i + m*j];
      else
        set_na(ret + i);
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_means_narm(cint m, cint n, const T *const restrict x, double *const restrict ret)
{
  int *nobs = (int*) malloc(m * sizeof(*nobs));
  if (nobs == NULL)
    return ALLOC_ERR;
  
  SAFE_FOR_SIMD
  for (int i=0; i<m; i++)
    nobs[i] = n;
  
  memset(ret, 0, m*sizeof(*ret));
  
  for (int j=0; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]))
        ret[i] += (double) x[i + m*j];
      else
        nobs[i]--;
    }
  }
  
  SAFE_FOR_SIMD
  for (int i=0; i<m; i++)
    ret[i] /= (double) nobs[i];
  
  free(nobs);
  
  return 0;
}



extern "C" {

int row_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return row_sums_narm(m, n, x, ret);
  else
    return row_sums_int_nonarm(m, n, x, ret);
}

int row_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return row_sums_narm(m, n, x, ret);
  else
    return row_sums_dbl_nonarm(m, n, x, ret);
}

int row_means_int(cbool narm, cint m, cint n, cint *const restrict x, double *const restrict ret)
{
  if (narm)
    return row_means_narm(m, n, x, ret);
  else
  {
    row_sums_int_nonarm(m, n, x, ret);
    return vec_scale(1.0/n, m, ret);
  }
  
}

int row_means_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return row_means_narm(m, n, x, ret);
  else
  {
    row_sums_dbl_nonarm(m, n, x, ret);
    return vec_scale(1.0/n, m, ret);
  }
}

}
