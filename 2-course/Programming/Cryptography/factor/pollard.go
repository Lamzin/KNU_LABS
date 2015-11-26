package factor


import (
	"math/rand"
	"../mymath"
)


func Pollard(n int64) (int64, bool) {
	cnt, times := 10, 10000
	
	arr := []int64{int64(1)}
	for i := 0; i < cnt; i++ {
		var r int64
		for r = rand.Int63() % 512 - 1024; r == 0 || r == -2; r = rand.Int63() % 512 - 1024 {
			//pass
		}
		arr = append(arr, r)
	} 

	for _, c := range arr {
		var a, b int64 = int64(2), int64(2)
		for i := 0; i < times; i++ {
			a = (a * a + c)	% n
			b = (b * b + c)	% n
			b = (b * b + c)	% n
			
			if a == b {
				break
			}

			if gcd := mymath.Gcd(a - b, n); gcd > 1 && gcd != n {
				return gcd, true
			}
		
		}	
	}
	
	return n, false
}