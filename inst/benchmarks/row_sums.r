library(rbenchmark)
library(mops)

m = 5000
n = 5000
x = matrix(rnorm(m*n), m, n)

cols <- cols <- c("test", "replications", "elapsed", "relative")

benchmark(a <- rowSums(x), b <- row_sums(x), columns=cols)
all.equal(a, b)
benchmark(a <- rowSums(x, na.rm=TRUE), b <- row_sums(x, na.rm=TRUE), columns=cols)
all.equal(a, b)
