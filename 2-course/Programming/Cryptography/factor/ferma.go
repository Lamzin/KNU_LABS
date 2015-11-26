package factor


import (
	"math"
	"../mymath"
)


func Ferma(n int64) (int64, bool) {
	sqrt := int64(math.Sqrt(float64(n)))
	
	for x := sqrt; 2 * x <= n; x++ {
		if y, res := mymath.IsSqr(x * x - n); res {
			return x - y, true
		}
	}
	
	return n, false
}