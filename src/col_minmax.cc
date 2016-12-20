#include "safeomp.h"
#include "mops.h"

#include "NA.hh"
#include "utils.hh"


template <typename T>
static inline bool get_first(cint m, cint n, cint j, int *const restrict start, const T *const restrict x, T *const restrict ret)
{
  while (*start < n && check_na(x[*start + m*j]))
    (*start)++;
  
  if (*start == n)
  {
    set_na(ret + j);
    return true;
  }
  else
  {
    ret[j] = x[*start + m*j];
    return false;
  }
}

template <typename T>
static inline int col_maxs_narm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    int start = 0;
    if (get_first(m, n, j, &start, x, ret))
      continue;
    
    SAFE_SIMD
    for (int i=start+1; i<m; i++)
    {
      if (ret[j] < x[i + m*j])
        ret[j] = x[i + m*j];
    }
  }
  
  return 0;
}

static inline int col_mins_int_narm(cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    int start = 0;
    if (get_first(m, n, j, &start, x, ret))
      continue;
    
    SAFE_SIMD
    for (int i=start+1; i<m; i++)
    {
      if (!check_na(ret[j]) && !check_na(x[i + m*j]) && x[i + m*j] < ret[j])
        ret[j] = x[i + m*j];
    }
  }
  
  return 0;
}

static inline int col_mins_dbl_narm(cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    int start = 0;
    if (get_first(m, n, j, &start, x, ret))
      continue;
    
    SAFE_SIMD
    for (int i=start+1; i<m; i++)
    {
      if (x[i + m*j] < ret[j])
        ret[j] = x[i + m*j];
    }
  }
  
  return 0;
}

template <typename T>
static inline int col_maxs_nonarm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = x[m*j];
    
    SAFE_SIMD
    for (int i=1; i<m; i++)
    {
      if (ret[j] < x[i + m*j])
        ret[j] = x[i + m*j];
    }
  }
  
  return 0;
}

template <typename T>
static inline int col_mins_nonarm(cint m, cint n, const T *const restrict x, T *const restrict ret)
{
  #pragma omp parallel for if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j++)
  {
    ret[j] = x[m*j];
    
    SAFE_SIMD
    for (int i=1; i<m; i++)
    {
      if (ret[j] > x[i + m*j])
        ret[j] = x[i + m*j];
    }
  }
  
  return 0;
}



extern "C" {

int col_mins_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return col_mins_int_narm(m, n, x, ret);
  else
    return col_mins_nonarm(m, n, x, ret);
}

int col_mins_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return col_mins_dbl_narm(m, n, x, ret);
  else
    return col_mins_nonarm(m, n, x, ret);
}

int col_maxs_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret)
{
  if (narm)
    return col_maxs_narm(m, n, x, ret);
  else
    return col_maxs_nonarm(m, n, x, ret);
}

int col_maxs_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret)
{
  if (narm)
    return col_maxs_narm(m, n, x, ret);
  else
    return col_maxs_nonarm(m, n, x, ret);
}

}
