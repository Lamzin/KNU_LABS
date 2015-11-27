package factor

import (
	"../mymath"
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
		P = append(P, r[i - 1] * Q[i - 1] - P[i - 1])
		Q = append(Q, Q[i - 2] + (P[i - 1] - P[i]) * r[i - 1])
		r = append(r, (P[i] + mymath.Sqrt(n)) / Q[i])
		
		if sqrt, ok := mymath.IsSqr(Q[i]); ok {
			d = sqrt
			break
		}
	}


	var Pnew, Qnew, rnew []int64
	Pnew = append(Pnew, -P[len(P) - 1])
	Qnew = append(Qnew, d)
	rnew = append(rnew, (Pnew[0] + mymath.Sqrt(n)) / Qnew[0])
	Pnew = append(Pnew, rnew[0] * Qnew[0] - Pnew[0])
	Qnew = append(Qnew, (n - Pnew[1] * Pnew[1]) / Qnew[0])

	rnew = append(rnew, rnew[0])

	
	for i := 2; true; i++ {
		Pnew = append(Pnew, rnew[i - 1] * Qnew[i - 1] - Pnew[i - 1])
		Qnew = append(Qnew, Qnew[i - 2] + (Pnew[i - 1] - Pnew[i]) * rnew[i - 1])
		rnew = append(rnew, (Pnew[i] + mymath.Sqrt(n)) / Qnew[i])
		
		if Pnew[i] == Pnew[i - 1] {
			return Qnew[i - 1], true
		}
	}
	
	return N, false
}