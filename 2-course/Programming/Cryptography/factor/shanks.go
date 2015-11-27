package factor

import (
	"../mymath"
	"fmt"
)


func Shanks(n int64) (int64, bool) {
	N := n
	if sqrt, ok := mymath.IsSqr(n); ok {
		return sqrt, true
	}
	
	if n % 4 == 1 {
		n *= 2
	}
	
	var P, Q, r []int64
	P = append(P, 0)
	P = append(P, mymath.Sqrt(n))
	r = append(r, mymath.Sqrt(n))
	Q = append(Q, 1)
	Q = append(Q, n - r[0] * r[0])
	r = append(r, 2 * r[0] / Q[1])

	var d int64
	for i := 2; true; i++ {
		P = append(P, r[1] * Q[1] - P[1])
		Q = append(Q, Q[0] + (P[1] - P[2]) * r[1])
		r = append(r, (P[2] + mymath.Sqrt(n)) / Q[2])
		
		if sqrt, ok := mymath.IsSqr(Q[2]); ok {
			d = sqrt
			break
		}
		
		P = P[1:3]
		Q = Q[1:3]
		r = r[1:3]
	}

	var Pnew, Qnew, rnew []int64
	
	Pnew = append(Pnew, -P[len(P) - 1])
	Qnew = append(Qnew, d)
	rnew = append(rnew, (Pnew[0] + mymath.Sqrt(n)) / Qnew[0])
	Pnew = append(Pnew, rnew[0] * Qnew[0] - Pnew[0])
	Qnew = append(Qnew, (n - Pnew[1] * Pnew[1]) / Qnew[0])

	//rnew = append(rnew, 3)
	rnew = append(rnew, (Pnew[1] + mymath.Sqrt(n)) / Qnew[1]) // What is real value to INIT ?!
	
	for i := 2; true; i++ {
		fmt.Println(Pnew, Qnew, rnew)

		Pnew = append(Pnew, rnew[1] * Qnew[1] - Pnew[1])
		Qnew = append(Qnew, Qnew[0] + (Pnew[1] - Pnew[2]) * rnew[1])
		rnew = append(rnew, (Pnew[2] + mymath.Sqrt(n)) / Qnew[2])
			
		if Pnew[2] == Pnew[1] {
			fmt.Println("Find:", Qnew[1])
			return Qnew[1], true
		}
		
		Pnew = Pnew[1:3]
		Qnew = Qnew[1:3]
		rnew = rnew[1:3]
	}
	
	return N, false
}