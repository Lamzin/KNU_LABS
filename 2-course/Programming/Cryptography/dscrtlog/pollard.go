package dscrtlog


import (
	"math/rand"
	"../mymath"
	"time"
	//"fmt"
)


func binpow(number, pow, module int64) int64 {
	res := int64(1)
	for pow != 0 {
		if pow % 2 == 1 {
			res = res * number % module		
		}
		number = number * number % module
		pow /= 2
	}
	return res
}


func reverse(number, module int64) int64 {
	return binpow(number, module - 2, module)
}


func Pollard(y, g, p int64) (x int64, ok bool) {
	seed := time.Now().UnixNano() // A new random seed (independent from state)
    rand.Seed(seed)
	
	
	var xarr, yarr, garr []int64
	xarr = append(xarr, y*y)
	yarr = append(yarr, 2)
	garr = append(garr, 0)
	
	for i := int64(0); i < p * 200; i++ {
		xtmp, ytmp, gtmp := xarr[i], yarr[i], garr[i] 
		
		switch rand.Intn(3) {
		case 0:
			xtmp = xtmp * y % p
			ytmp = (ytmp + 1) //% (p - 1)
		case 1:
			xtmp = xtmp * xtmp % p
			ytmp = (ytmp * 2) //% (p - 1)
			gtmp = (gtmp * 2) //% (p - 1)
		case 2:
			xtmp = xtmp * g % p
			gtmp = (gtmp + 1) //% (p - 1)
		}	
		
		xarr = append(xarr, xtmp)
		yarr = append(yarr, ytmp)
		garr = append(garr, gtmp)		
		
		if i % 2 == 0 && i > 0 && xarr[i] == xarr[i / 2] {
			ydelta  := (yarr[i / 2] - yarr[i]    ) % (p - 1)
			gdelta  := (garr[i]     - garr[i / 2]) % (p - 1)			
			if ydelta < 0 {
				ydelta += p - 1
			}
			if gdelta < 0 {
				gdelta += p - 1
			}
			gcd 	:= mymath.Gcd(ydelta, p - 1)			
			
			if ydelta == 0 {
//				x, ok  = p, false
//				return
			} else if gdelta % gcd == 0 {
				ydelta /= gcd
				gdelta /= gcd
				mod    := (p - 1) / gcd
						
				for cur := reverse(ydelta, mod) * gdelta % mod; cur < p - 1; cur += mod {				
					if binpow(g, cur, p) == y {
						x, ok = cur, true
						return
					}
				}
			}
		}
	}
	
	x, ok = p, false
	return
}