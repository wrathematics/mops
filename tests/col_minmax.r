library(mops)
set.seed(12345)

colMins = function(x, na.rm) apply(x, MARGIN=2, min, na.rm=na.rm)
mins = function(x, na.rm) stopifnot(all.equal(colMins(x, na.rm), col_mins(x, na.rm)))

colMaxs = function(x, na.rm) apply(x, MARGIN=2, max, na.rm=na.rm)
maxs = function(x, na.rm) stopifnot(all.equal(colMaxs(x, na.rm), col_maxs(x, na.rm)))

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
