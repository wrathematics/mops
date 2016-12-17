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
