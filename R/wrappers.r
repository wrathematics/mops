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
#' The functions handle \code{NA}'s appropriately.
#' 
#' @param x
#' A numeric (integer or double) or logical matrix.
#' 
#' @name rc_minmax
#' @rdname rc_minmax
NULL

#' @rdname rc_minmax
#' @export
col_mins <- function(x) .Call(R_col_mins, x)

#' @rdname rc_minmax
#' @export
row_mins <- function(x) .Call(R_row_mins, x)

#' @rdname rc_minmax
#' @export
col_maxs <- function(x) .Call(R_col_maxs, x)

#' @rdname rc_minmax
#' @export
row_maxs <- function(x) .Call(R_row_maxs, x)
