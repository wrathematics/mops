#' Matrix Row/Col Sums/Means
#' 
#' Optimized versions of R's \code{rowSums()}, \code{colSums()}, \code{rowMeans()}, and \code{colMeans()}.
#' 
#' @param x
#' A numeric (integer or double) or logical matrix.
#' @param na.rm
#' Should \code{NA} values be removed?
#' 
#' @name rc_sums
#' @rdname rc_sums
NULL

#' @rdname rc_sums
#' @export
col_sums <- function(x, na.rm=FALSE) .Call(R_col_sums, x, na.rm)

#' @rdname rc_sums
#' @export
row_sums <- function(x, na.rm=FALSE) .Call(R_row_sums, x, na.rm)

#' @rdname rc_sums
#' @export
col_means <- function(x, na.rm=FALSE) .Call(R_col_means, x, na.rm)

#' @rdname rc_sums
#' @export
row_means <- function(x, na.rm=FALSE) .Call(R_row_means, x, na.rm)



#' Matrix Row/Col Min/Maxes
#' 
#' Row/Column minimum/maximum values. Analogues of e.g. \code{colSums()} and \code{rowSums()}.
#' 
#' @param x
#' A numeric (integer or double) or logical matrix.
#' @param na.rm
#' Should \code{NA} values be removed?
#' 
#' @name rc_minmax
#' @rdname rc_minmax
NULL

#' @rdname rc_minmax
#' @export
col_mins <- function(x, na.rm=FALSE) .Call(R_col_mins, x, na.rm)

#' @rdname rc_minmax
#' @export
row_mins <- function(x, na.rm=FALSE) .Call(R_row_mins, x, na.rm)

#' @rdname rc_minmax
#' @export
col_maxs <- function(x, na.rm=FALSE) .Call(R_col_maxs, x, na.rm)

#' @rdname rc_minmax
#' @export
row_maxs <- function(x, na.rm=FALSE) .Call(R_row_maxs, x, na.rm)



#' Matrix Row/Col Any/All
#' 
#' Row/Column any/all values. Analogues of e.g. \code{colSums()} and \code{rowSums()}.
#' 
#' @details
#' If \code{na.rm=FALSE}, then \code{NA}'s are ignored.  If, for example, we 
#' have a column of all \code{NA} values, \code{col_anys()} will return 
#' \code{FALSE} and \code{col_all()} will return \code{TRUE}.
#' 
#' @param x
#' A numeric (integer or double) or logical matrix.
#' @param na.rm
#' Should \code{NA} values be removed?
#' 
#' @name rc_anyall
#' @rdname rc_anyall
NULL

#' @rdname rc_anyall
#' @export
col_anys <- function(x, na.rm=FALSE) .Call(R_col_anys, x, na.rm)

#' @rdname rc_anyall
#' @export
row_anys <- function(x, na.rm=FALSE) .Call(R_row_anys, x, na.rm)

#' @rdname rc_anyall
#' @export
col_alls <- function(x, na.rm=FALSE) .Call(R_col_alls, x, na.rm)

#' @rdname rc_anyall
#' @export
row_alls <- function(x, na.rm=FALSE) .Call(R_row_alls, x, na.rm)
