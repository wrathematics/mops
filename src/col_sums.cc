#include "safeomp.h"
#include "config.h"

template <typename T>
static inline int col_sums(const int m, const int n, const T*const restrict x, T*const restrict ret)
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



extern "C" int col_sums_int(const int m, const int n, const int*const restrict x, int *const restrict ret)
{
  return col_sums(m, n, x, ret);
}

extern "C" int col_sums_dbl(const int m, const int n, const double*const restrict x, double *const restrict ret)
{
  return col_sums(m, n, x, ret);
}
