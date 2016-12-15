#ifndef MOPS_H_
#define MOPS_H_

#include "config.h"

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif


typedef const int cint;
typedef const bool cbool;
typedef const double cdbl;

// col_sums.cc
int col_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int col_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);

// row_sums.cc
int row_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int row_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);


#ifdef __cplusplus
}
#endif

#endif
