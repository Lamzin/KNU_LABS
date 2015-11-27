package dscrtlog


func Primitive(y, g, p int64) (x int64, ok bool) {
	x, ok = int64(1), true
	cur := g
	for cur != y {
		cur = (cur * g) % p 
		x++
		if cur == g % p {
			ok = false
			return	
		} 	
	}
	
	return	
}