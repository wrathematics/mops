#include <Rinternals.h>

int col_sums_int(const int m, const int n, const int*const restrict x, int *const restrict ret);
int col_sums_dbl(const int m, const int n, const double*const restrict x, double *const restrict ret);


SEXP R_col_sums(SEXP x)
{
  SEXP ret;
  const int m = nrows(x);
  const int n = ncols(x);
  
  switch (TYPEOF(x))
  {
    case LGLSXP:
      PROTECT(ret = allocVector(LGLSXP, n));
      col_sums_int(m, n, INTEGER(x), INTEGER(ret));
      break;
    
    case INTSXP:
      PROTECT(ret = allocVector(INTSXP, n));
      col_sums_int(m, n, INTEGER(x), INTEGER(ret));
      break;
    
    case REALSXP:
    PROTECT(ret = allocVector(REALSXP, n));
    col_sums_dbl(m, n, REAL(x), REAL(ret));
    break;
    
    default:
      error("argument 'x' must be numeric");
  }
  
  UNPROTECT(1);
  return ret;
}
