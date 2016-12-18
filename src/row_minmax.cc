#include <string.h>

#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T>
static inline int row_mins(cint m, cint n, const T *const restrict x, T *const restrict ret)
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
static inline int row_maxs(cint m, cint n, const T *const restrict x, T *const restrict ret)
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



extern "C" {

int row_mins_int(cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  return row_mins(m, n, x, ret);
}

int row_mins_dbl(cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  return row_mins(m, n, x, ret);
}

int row_maxs_int(cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  return row_maxs(m, n, x, ret);
}

int row_maxs_dbl(cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  return row_maxs(m, n, x, ret);
}

}
