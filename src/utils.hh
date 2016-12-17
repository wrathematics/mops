#ifndef MOPS_UTILS_H
#define MOPS_UTILS_H

#include "NA.hh"

static inline int vec_scale(cdbl alpha, cint len, double *const restrict ret)
{
  SAFE_FOR_SIMD
  for (int j=0; j<len; j++)
    ret[j] *= alpha;
  
  return 0;
}

#endif
