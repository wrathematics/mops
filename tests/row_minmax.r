library(mops)
set.seed(12345)

rowMins = function(x) apply(x, MARGIN=1, min, na.rm=TRUE)
mins = function(x) stopifnot(all.equal(rowMins(x), row_mins(x)))

rowMaxs = function(x) apply(x, MARGIN=1, max, na.rm=TRUE)
maxs = function(x) stopifnot(all.equal(rowMaxs(x), row_maxs(x)))

m = 30
n = 10
x = matrix(rnorm(m*n, 1000, 200), m, n)

mins(x)
mins(t(x))

maxs(x)
maxs(t(x))

x[c(1, 7, 99)] = NA
mins(x)
mins(t(x))

maxs(x)
maxs(t(x))



storage.mode(x) = "integer"
mins(x)
mins(t(x))

maxs(x)
maxs(t(x))
