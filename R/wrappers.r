#' @export
col_sums <- function(x, na.rm=FALSE) .Call(R_col_sums, x, na.rm)

#' @export
row_sums <- function(x, na.rm=FALSE) .Call(R_row_sums, x, na.rm)
