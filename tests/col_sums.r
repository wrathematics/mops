library(mops)

m = 30
n = 10
x = matrix(rnorm(m*n), m, n)

stopifnot(all.equal(colSums(x), col_sums(x)))

