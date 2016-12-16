library(mops)
set.seed(12345)

test = function(x, na.rm) stopifnot(all.equal(rowSums(x, na.rm), row_sums(x, na.rm)))
m = 30
n = 10
x = matrix(rnorm(m*n), m, n)

test(x, FALSE)
test(t(x), FALSE)

test(x, TRUE)
x[c(1, 7, 99)] = NA
test(x, TRUE)
test(t(x), TRUE)


storage.mode(x) = "integer"
test(x, FALSE)
test(t(x), FALSE)
