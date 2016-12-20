#include <string.h>

#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T>
static inline int row_mins_narm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  memcpy(ret, x, m*sizeof(*ret));
  
  for (int j=1; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (check_na(ret[i]) || (!check_na(x[i + m*j]) && ret[i] > x[i + m*j]))
        ret[i] = x[i + m*j];
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_mins_nonarm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  memcpy(ret, x, m*sizeof(*ret));
  
  for (int j=1; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (ret[i] > x[i + m*j])
        ret[i] = x[i + m*j];
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_maxs_narm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  memcpy(ret, x, m*sizeof(*ret));
  
  for (int j=1; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (check_na(ret[i]) || (!check_na(x[i + m*j]) && ret[i] < x[i + m*j]))
        ret[i] = x[i + m*j];
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_maxs_nonarm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  memcpy(ret, x, m*sizeof(*ret));
  
  for (int j=1; j<n; j++)
  {
    #pragma omp parallel for if(m>=OMP_MIN_SIZE)
    for (int i=0; i<m; i++)
    {
      if (ret[i] < x[i + m*j])
        ret[i] = x[i + m*j];
    }
  }
  
  return 0;
}



extern "C" {

int row_mins_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return row_mins_narm(m, n, x, ret);
  else
    return row_mins_nonarm(m, n, x, ret);
}

int row_mins_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return row_mins_narm(m, n, x, ret);
  else
    return row_mins_nonarm(m, n, x, ret);
}

int row_maxs_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return row_maxs_narm(m, n, x, ret);
  else
    return row_maxs_nonarm(m, n, x, ret);
}

int row_maxs_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return row_maxs_narm(m, n, x, ret);
  else
    return row_maxs_nonarm(m, n, x, ret);
}

}
