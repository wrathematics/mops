library(mops)
set.seed(12345)

sums = function(x, na.rm) stopifnot(all.equal(colSums(x, na.rm), col_sums(x, na.rm)))
means = function(x, na.rm) stopifnot(all.equal(colMeans(x, na.rm), col_means(x, na.rm)))

m = 30
n = 10
x = matrix(rnorm(m*n, 1000, 200), m, n)

sums(x, FALSE)
sums(t(x), FALSE)

means(x, FALSE)
means(t(x), FALSE)


sums(x, TRUE)
x[c(1, 7, 99)] = NA
sums(x, TRUE)
sums(t(x), TRUE)

means(x, TRUE)
x[c(1, 7, 99)] = NA
means(x, TRUE)
means(t(x), TRUE)



storage.mode(x) = "integer"
sums(x, FALSE)
sums(t(x), FALSE)

means(x, FALSE)
means(t(x), FALSE)
