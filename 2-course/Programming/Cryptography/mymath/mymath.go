package mymath


import "math"


func Gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a % b
	}
	return a
}


func IsSqr(n int64) (int64, bool) {
	sqrt := int64(math.Sqrt(float64(n)))
	
	for i := sqrt - 2; i < sqrt + 3; i++ {
		if i * i == n {
			return i, true
		}
	}
	return sqrt, false
}


func IsSimple(n int64) bool {
	if n == 2 {
		return true	
	} else if n % 2 == 0 {
		return false
	}
	
	for i := int64(3); i * i <= n; i += 2 {
		if n % i == 0 {
			return false	
		}
	}
	
	return true
}


func IsQuadraticResidue(n, p int64) bool {
	for i := int64(1); i < p; i++ {
		residue := i
		for pow := int64(2); pow <= 2 * p; pow += 2 {
			if residue == n % p {
				return true
			}
			residue = residue * residue % p	
		}
	}
	
	return false
}