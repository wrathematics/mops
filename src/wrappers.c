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

#define CALLFUN(fun) \
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



SEXP R_col_sums(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  const int m = nrows(x);
  const int n = ncols(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(n);
  CALLFUN(col_sums);
  
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
  CALLFUN(row_sums);  
  
  UNPROTECT(1);
  return ret;
}
