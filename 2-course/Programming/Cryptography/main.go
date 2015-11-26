package main

import (
	"fmt"
	"./factor"
)


func main() {
	var algorithms []factor.Algo
	
	algorithms = append(algorithms, factor.Ferma)
	algorithms = append(algorithms, factor.Pollard)
	algorithms = append(algorithms, factor.Quadratic)	

	var n int64 = 19939//15341//24961//1993901//15341//19939
	
	fmt.Println("n = ", n)
	for _, algo := range algorithms {
		fmt.Println(factor.Factor(n, algo))	
	}
	
}