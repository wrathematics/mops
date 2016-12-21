#include "mops.h"
#include "wrappers.h"


SEXP R_col_sums(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
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



SEXP R_col_mins(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(n);
  CALLFUN_NA(col_mins);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_col_maxs(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(n);
  CALLFUN_NA(col_maxs);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_mins(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(m);
  CALLFUN_NA(row_mins);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_maxs(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC(m);
  CALLFUN_NA(row_maxs);
  
  UNPROTECT(1);
  return ret;
}



SEXP R_col_anys(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC_LGL(n);
  CALLFUN_INTRET_NA(col_anys);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_col_alls(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC_LGL(n);
  CALLFUN_INTRET_NA(col_alls);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_anys(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC_LGL(m);
  CALLFUN_INTRET_NA(row_anys);
  
  UNPROTECT(1);
  return ret;
}

SEXP R_row_alls(SEXP x, SEXP narm)
{
  SEXP ret;
  CHECK_IS_MATRIX(x);
  
  CHECK_IS_FLAG(narm);
  NEWVEC_LGL(m);
  CALLFUN_INTRET_NA(row_alls);
  
  UNPROTECT(1);
  return ret;
}
