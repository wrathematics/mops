library(rbenchmark)
library(mops)

m = 5000
n = 5000
x = matrix(rnorm(m*n), m, n)

cols <- cols <- c("test", "replications", "elapsed", "relative")

benchmark(a <- rowMeans(x), b <- row_means(x), columns=cols)
all.equal(a, b)
benchmark(a <- rowMeans(x, na.rm=TRUE), b <- row_means(x, na.rm=TRUE), columns=cols)
all.equal(a, b)
