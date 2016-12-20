library(mops)
set.seed(12345)

rowMins = function(x, na.rm) apply(x, MARGIN=1, min, na.rm=na.rm)
mins = function(x, na.rm) stopifnot(all.equal(rowMins(x, na.rm), row_mins(x, na.rm)))

rowMaxs = function(x, na.rm) apply(x, MARGIN=1, max, na.rm=na.rm)
maxs = function(x, na.rm) stopifnot(all.equal(rowMaxs(x, na.rm), row_maxs(x, na.rm)))

m = 30
n = 10
x = matrix(rnorm(m*n, 1000, 200), m, n)

mins(x, FALSE)
mins(t(x), FALSE)

maxs(x, FALSE)
maxs(t(x), FALSE)

x[c(1, 7, 99)] = NA
mins(x, TRUE)
mins(t(x), TRUE)

maxs(x, TRUE)
maxs(t(x), TRUE)



storage.mode(x) = "integer"
mins(x, TRUE)
mins(t(x), TRUE)

maxs(x, TRUE)
maxs(t(x), TRUE)
