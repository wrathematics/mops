# mops

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/mops.png)](https://travis-ci.org/wrathematics/mops)
* **License:** [![License](http://img.shields.io/badge/license-BSD%202--Clause-orange.svg?style=flat)](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


Optimized matrix operations, such as row/col sums.

```r
library(rbenchmark)
library(mops)

m = 5000
n = 5000
x = matrix(rnorm(m*n), m, n)
cols <- cols <- c("test", "replications", "elapsed", "relative")

benchmark(a <- colSums(x), b <- col_sums(x), columns=cols)
##               test replications elapsed relative
## 1  a <- colSums(x)          100   2.554    2.234
## 2 b <- col_sums(x)          100   1.143    1.000
all.equal(a, b)
## [1] TRUE

benchmark(a <- rowSums(x), b <- row_sums(x), columns=cols)
##               test replications elapsed relative
## 1  a <- rowSums(x)          100   7.102    4.478
## 2 b <- row_sums(x)          100   1.586    1.000
all.equal(a, b)
## [1] TRUE
```
