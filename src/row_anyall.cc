#include <string.h>

#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T>
static inline int row_anys(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  memset(ret, 0, m*sizeof(*ret));
  
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
    {
      if (x[i + m*j])
        ret[i] = 1;
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_alls(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  SAFE_FOR_SIMD
  for (int i=0; i<m; i++)
    ret[i] = 1;
  
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
    {
      if (!x[i + m*j])
        ret[i] = 0;
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_anys_narm(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  memset(ret, 0, m*sizeof(*ret));
  
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]) && x[i + m*j])
        ret[i] = 1;
    }
  }
  
  return 0;
}

template <typename T>
static inline int row_alls_narm(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  SAFE_FOR_SIMD
  for (int i=0; i<m; i++)
    ret[i] = 1;
  
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]) && !x[i + m*j])
        ret[i] = 0;
    }
  }
  
  return 0;
}



extern "C" {

int row_anys_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return row_anys_narm(m, n, x, ret);
  else
    return row_anys(m, n, x, ret);
}

int row_anys_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, int *const restrict ret)
{
  return row_anys(m, n, x, ret);
}

int row_alls_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return row_alls_narm(m, n, x, ret);
  else
    return row_alls(m, n, x, ret);
}

int row_alls_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, int *const restrict ret)
{
  return row_alls(m, n, x, ret);
}

}
