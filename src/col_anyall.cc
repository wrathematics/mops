#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T>
static inline int col_anys(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    for (int i=0; i<m; i++)
    {
      if (x[i + m*j])
      {
        ret[j] = 1;
        break;
      }
    }
  }
  
  return 0;
}

template <typename T>
static inline int col_alls(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 1;
    
    for (int i=0; i<m; i++)
    {
      if (!x[i + m*j])
      {
        ret[j] = 0;
        break;
      }
    }
  }
  
  return 0;
}

template <typename T>
static inline int col_anys_narm(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 0;
    
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]) && x[i + m*j])
      {
        ret[j] = 1;
        break;
      }
    }
  }
  
  return 0;
}

template <typename T>
static inline int col_alls_narm(cint m, cint n, const T *const restrict x, int *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = 1;
    
    for (int i=0; i<m; i++)
    {
      if (!check_na(x[i + m*j]) && !x[i + m*j])
      {
        ret[j] = 0;
        break;
      }
    }
  }
  
  return 0;
}



extern "C" {

int col_anys_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return col_anys_narm(m, n, x, ret);
  else
    return col_anys(m, n, x, ret);
}

int col_anys_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, int *const restrict ret)
{
  return col_anys(m, n, x, ret);
}

int col_alls_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return col_alls_narm(m, n, x, ret);
  else
    return col_alls(m, n, x, ret);
}

int col_alls_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, int *const restrict ret)
{
  return col_alls(m, n, x, ret);
}

}
