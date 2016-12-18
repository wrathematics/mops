#include <Rinternals.h>
#include "mops.h"

#define LGLP(x) LOGICAL(x)
#define INTP(x) INTEGER(x)
#define DBLP(x) REAL(x)

#define LGL(x) LOGICAL(x)[0]
#define INT(x) INTEGER(x)[0]
#define DBL(x) REAL(x)[0]

#define CHECK_IS_MATRIX(x) \
  if (!isMatrix(x)){error("argument '" #x "' must be a matrix");}

#define CHECK_IS_FLAG(x) \
  if (TYPEOF(x) != LGLSXP || LENGTH(x) != 1){error("argument '" #x "' must be a flag");}

#define THROW_TYPE_ERR error("argument 'x' must be numeric or logical")

#define NEWVEC(len) \
  switch (TYPEOF(x)){ \
    case LGLSXP: \
    case INTSXP: \
      PROTECT(ret = allocVector(INTSXP, len)); \
      break; \
    case REALSXP: \
      PROTECT(ret = allocVector(REALSXP, len)); \
      break; \
    default: \
      THROW_TYPE_ERR;}

#define CALLFUN_NA(fun) \
switch (TYPEOF(x)){ \
  case LGLSXP: \
  case INTSXP: \
    fun ## _int(LGL(narm), m, n, INTP(x), INTP(ret)); \
    break; \
  case REALSXP: \
    fun ## _dbl(LGL(narm), m, n, DBLP(x), DBLP(ret)); \
    break; \
  default: \
    THROW_TYPE_ERR;}

#define CALLFUN(fun) \
switch (TYPEOF(x)){ \
  case LGLSXP: \
  case INTSXP: \
    fun ## _int(m, n, INTP(x), INTP(ret)); \
    break; \
  case REALSXP: \
    fun ## _dbl(m, n, DBLP(x), DBLP(ret)); \
    break; \
  default: \
    THROW_TYPE_ERR;}



SEXP R_col_sums(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(n);
  CALLFUN_NA(col_sums);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_sums(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(m);
  CALLFUN_NA(row_sums);
  
  UNPROTECT(1);
  return ret;
}



SEXP R_col_means(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  CHECK_IS_FLAG(narm);
  PROTECT(ret = allocVector(REALSXP, n));
  switch (TYPEOF(x))
  {
    case LGLSXP:
    case INTSXP:
      col_means_int(LGL(narm), m, n, INTP(x), DBLP(ret));
      break;
    case REALSXP:
      col_means_dbl(LGL(narm), m, n, DBLP(x), DBLP(ret));
      break;
    default:
      THROW_TYPE_ERR;
  }
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_means(SEXP x, SEXP narm)
{
  SEXP ret;
  int check;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  CHECK_IS_FLAG(narm);
  PROTECT(ret = allocVector(REALSXP, m));
  switch (TYPEOF(x))
  {
    case LGLSXP:
    case INTSXP:
      check = row_means_int(LGL(narm), m, n, INTP(x), DBLP(ret));
      break;
    case REALSXP:
      check = row_means_dbl(LGL(narm), m, n, DBLP(x), DBLP(ret));
      break;
    default:
      THROW_TYPE_ERR;
  } 
  
  if (check)
    error("unable to allocated needed memory (%d*4 bytes)", m);
  
  UNPROTECT(1);
  return ret;
}



SEXP R_col_mins(SEXP x)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  NEWVEC(n);
  CALLFUN(col_mins);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_col_maxs(SEXP x)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  NEWVEC(n);
  CALLFUN(col_maxs);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_mins(SEXP x)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  NEWVEC(m);
  CALLFUN(row_mins);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_maxs(SEXP x)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  NEWVEC(m);
  CALLFUN(row_maxs);
  
  UNPROTECT(1);
  return ret;
}
