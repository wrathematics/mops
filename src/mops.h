#ifndef MOPS_H_
#define MOPS_H_

#include "config.h"

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#define ALLOC_ERR -1

typedef const int cint;
typedef const bool cbool;
typedef const double cdbl;


// col_minmax.cc
int col_mins_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int col_mins_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);
int col_maxs_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int col_maxs_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);

// row_minmax.cc
int row_mins_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int row_mins_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);
int row_maxs_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int row_maxs_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);

// col_sums.cc
int col_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int col_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);
int col_means_int(cbool narm, cint m, cint n, cint *const restrict x, double *const restrict ret);
int col_means_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);

// row_sums.cc
int row_sums_int(cbool narm, cint m, cint n, cint *const restrict x, int *const restrict ret);
int row_sums_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);
int row_means_int(cbool narm, cint m, cint n, cint *const restrict x, double *const restrict ret);
int row_means_dbl(cbool narm, cint m, cint n, cdbl *const restrict x, double *const restrict ret);


#ifdef __cplusplus
}
#endif

#endif
