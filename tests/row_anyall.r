library(mops)
set.seed(12345)

rowAnys = function(x, na.rm) apply(x, MARGIN=1, any, na.rm=na.rm)
anys = function(x, na.rm) stopifnot(all.equal(rowAnys(x, na.rm), row_anys(x, na.rm)))

rowAlls = function(x, na.rm) apply(x, MARGIN=1, all, na.rm=na.rm)
alls = function(x, na.rm) stopifnot(all.equal(rowAlls(x, na.rm), row_alls(x, na.rm)))

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
