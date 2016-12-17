library(rbenchmark)
library(mops)

m = 5000
n = 5000
x = matrix(rnorm(m*n), m, n)

cols <- cols <- c("test", "replications", "elapsed", "relative")

benchmark(a <- colMeans(x), b <- col_means(x), columns=cols)
all.equal(a, b)
benchmark(a <- colMeans(x, na.rm=TRUE), b <- col_means(x, na.rm=TRUE), columns=cols)
all.equal(a, b)
