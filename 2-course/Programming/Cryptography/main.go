package main

import (
	"fmt"
	"./factor"
	"./dscrtlog"
)


func test_factorization() {
	//445623461  = [19069 23369]
	//3230893777 = [33461 96557] -param={20, 20}
	var n int64 = 15341//24961//1993901//15341//19939
	var algorithms []factor.Algo
	
	algorithms = append(algorithms, factor.Ferma)
	algorithms = append(algorithms, factor.Pollard)
	algorithms = append(algorithms, factor.Quadratic)	


	fmt.Println("n = ", n)
	for _, algo := range algorithms {
		fmt.Println(factor.Factor(n, algo))	
	}


}


func test_discrete_logarithm() {
	var y, g, p int64 = int64(9), int64(2), int64(19)
	var algorithms []dscrtlog.Algo

	
	algorithms = append(algorithms, dscrtlog.Primitive)
	algorithms = append(algorithms, dscrtlog.Shank)
	algorithms = append(algorithms, dscrtlog.Pollard)
	
	fmt.Println("y =", y, "; g =", g, "; p =", p, ":")
	for _, algo := range algorithms {
		if x, ok := algo(y, g, p); ok {
			fmt.Println("x =", x)			
		} else {
			fmt.Println("Doesn't exist!")	
		}
	}
}


func main() {

	test_factorization()
	
	test_discrete_logarithm()

}