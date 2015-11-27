package factor


//import "fmt"


func Factor(n int64, f Algo) []int64 {
	var que, arr []int64
	que = append(que, n)
	
	for i := 0; i < len(que); i++ {
		if val, ok := f(que[i]); ok && val * val > 1 && val != que[i] && -val != que[i] {
			que = append(que, val)
			que = append(que, que[i] / val)
		} else {
			arr = append(arr, que[i])
		}
	}
	
	return arr
}