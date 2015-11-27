package dscrtlog


import (
	"sort"
	"../mymath"
)


type pair 		[2]int64
type pairArr 	[]pair


func (a pairArr) Len() int {
	return len(a)	
}


func (a pairArr) Less(i, j int) bool {
	if a[i][0] != a[j][0] {
		return a[i][0] < a[j][0]
	} else {
		return a[i][1] < a[j][1]
	}
}


func (a pairArr) Swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}


func Shank(y, g, p int64) (x int64, ok bool) {
	var L1, L2 	pairArr
	var sqrt 	int64
	
	gpow, gL1 := int64(1), int64(1)
	
	
	if sqrt_val, ok := mymath.IsSqr(p); ok {
		sqrt = sqrt_val
	} else {
		sqrt = sqrt_val + 1
	}
	
	
	for i := int64(0); i < sqrt; i++ {
		L2 = append(L2, pair{y * gpow % p, i})
		gpow = gpow * g % p
	}
	
	for i := int64(0); i <= sqrt; i++ {
		L1 = append(L1, pair{gL1, sqrt * i})
		gL1 = gL1 * gpow % p	
	}
	
	sort.Sort(L1)
	sort.Sort(L2)
	
	i, j := 0, 0
	for i < len(L1) && j < len(L2) {
		if L1[i][0] == L2[j][0] {
			x  = (L1[i][1] - L2[j][1]) % (p - 1)
			if x < 0 {
				x = (p - 1) + x
			}
			ok = true
			return
		} else if L1[i][0] < L2[j][0] {
			i++	
		} else {
			j++	
		}
	}
	
	x, ok = p, false
	return
}