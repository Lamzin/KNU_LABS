package factor


import (
	"math"
	"../mymath"
	//"fmt"
)


func isFactorByBase(n int64, base *[]int64) (arr, full []int, bresult bool) {	
	for i, val := range *base {
		arr		= append(arr, 0)
		full 	= append(full, 0)
		
		if val * val < 2 || n == 0 { // val != {-1, 0, 1}
			if val == -1 && n < 0{
				arr[i] 	= 1	
				full[i] = 1
			}
			continue	
		} 
		
		for n % val == 0 {
			n 		/= val
			arr[i] 	^= 1
			full[i] += 1
		}
	}
	bresult = (n == 1) || (n == -1)
	
	return 
}


func makeBase(n int64, sz int) (arr []int64){
	if mymath.IsSimple(2) && mymath.IsQuadraticResidue(n, 2) {
		arr = append(arr, 2)	
	}
	
	for p, cnt := int64(3), 0; cnt < sz; p += 2 {
		if mymath.IsSimple(p) && mymath.IsQuadraticResidue(n, p) {
			arr = append(arr, p)	
			cnt += 1
		}
	}
	
	return
}


type fctr struct { // "fctr" = factor
	a, b int64
	vector, full []int	
}


func NewFctr(a, b int64, vector, full []int) (f fctr) {
	f.a, f.b = a, b
	f.vector, f.full = vector, full
	return
}


func Quadratic(n int64) (int64, bool) {
	basesz := 10
	baseF := []int64{int64(-1)}
	baseF = append(baseF, makeBase(n, basesz - 1)...)
	
	var setT []fctr
	sqrt := int64(math.Sqrt(float64(n)))
	for xx := int64(0); len(setT) != basesz; xx++ {
		x := xx / 2
		if xx % 2 == 1 {
			x = -x - 1
		}
		
		a := x + sqrt
		b := a * a - n
		vect, full, ok :=  isFactorByBase(b, &baseF)
		if ok {
			setT = append(setT, NewFctr(a, b, vect, full))	
		}
	}
	
	var index []int
	curvector , curfull := make([]int, basesz), make([]int, basesz)
	

	var dfs func (int) (int64, bool)
	dfs = func (deep int) (divider int64, ok bool){
		allzero := true
		
		if deep != -1 {
			index = append(index, deep)
			for i := 0; i < basesz; i++ {
				curvector[i] ^= setT[deep].vector[i]
				curfull[i] 	 += setT[deep].full[i]
				if curvector[i] == 1 {
					allzero = false	
				}
			}
			
			if allzero {
				var a, b int64 = int64(1), int64(1)
				for _, i := range index {
					if setT[i].a < 0 {
						a = a * (-setT[i].a) % n
					} else {
						a = a * setT[i].a % n
					}			
				}
				
				for i := 0; i < basesz; i++ {
					for j := 0; 2 * j < curfull[i]; j++ {
						b = (b * baseF[i]) % n; // b ^ pow % n
					}	
				}

				if gcd := mymath.Gcd(a - b, n); gcd > 1 && gcd != n {
					divider = gcd
					ok 		= true
					return
				}
			}
		}
				
		for i := deep + 1; i < basesz; i++ {
			div, okk := dfs(i)
			if okk {
				divider = div
				ok 		= okk
				return	
			}
		}	
		
		if deep != -1 {
			index = index[0 :  len(index) - 1]	
			for i := 0; i < basesz; i++ {
				curvector[i] ^= setT[deep].vector[i]	
				curfull[i] 	 -= setT[deep].full[i]
			}	
		}
		
		divider = n
		ok 		= false
		return
	}


	return dfs(-1)
}