library(mops)
set.seed(12345)

colAnys = function(x, na.rm) apply(x, MARGIN=2, any, na.rm=na.rm)
anys = function(x, na.rm) stopifnot(all.equal(colAnys(x, na.rm), col_anys(x, na.rm)))

colAlls = function(x, na.rm) apply(x, MARGIN=2, all, na.rm=na.rm)
alls = function(x, na.rm) stopifnot(all.equal(colAlls(x, na.rm), col_alls(x, na.rm)))

m = 30
n = 10
x = matrix(sample(c(TRUE, FALSE), m*n, TRUE), m, n)

anys(x, FALSE)
anys(t(x), FALSE)

alls(x, FALSE)
alls(t(x), FALSE)

x[c(1, 7, 99)] = NA

anys(x, TRUE)
anys(t(x), TRUE)

alls(x, TRUE)
alls(t(x), TRUE)



storage.mode(x) = "integer"
x = x*2
anys(x, TRUE)
anys(t(x), TRUE)

alls(x, TRUE)
alls(t(x), TRUE)
