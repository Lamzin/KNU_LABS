package main

import (
	"../gauss"
	"fmt"
	"math"
)

func main() {
	task := Task{
		N: 4,
		A: 1.0,
		B: 3.0,
		K: 1.0,
		C: 1.0,
		W: 0.5,
	}
	task.F = getFunction(task.K, task.C, task.W)
	task.Phis = getSystemOfExponentialFunctions(task.N + 1)
	//task.Phis = getSystemOfLegendreFunctions(task.N + 1)
	//task.Phis = getSystemOfPolynomicalFunctions(task.N + 1)

	task.Solve()
	fmt.Println(task.GetExponentialFormula())
	//fmt.Println(task.GetLegendreFormula())
	//fmt.Println(task.GetPolynomsFormula())
	fmt.Printf("Deviation: %6.6f\n", task.GetDeviation())
}

type F func(float64) float64

func integrate(f F, a float64, b float64) (I float64) {
	if a > b {
		panic("a > b")
	}
	delta := (b - a) / 100000.0
	for ; a < b; a += delta {
		I += delta * f(a)
	}
	return
}

func scalarProduction(f, g F, a, b float64) float64 {
	h := func(x float64) float64 {
		return f(x) * g(x)
	}
	return integrate(h, a, b)
}

func getSystemOfLegendreFunctions(n int) []F {
	fs := make([]F, 6)

	fs[0] = func(x float64) float64 {
		return 1
	}
	fs[1] = func(x float64) float64 {
		return x
	}
	fs[2] = func(x float64) float64 {
		return (3.0*x*x - 1) / 2.0
	}
	fs[3] = func(x float64) float64 {
		return (5.0*x*x*x - 3.0*x) / 2.0
	}
	fs[4] = func(x float64) float64 {
		return (35.0*x*x*x*x - 30.0*x*x + 3) / 8.0
	}
	fs[5] = func(x float64) float64 {
		return (63.0*x*x*x*x*x - 70.0*x*x*x + 15.0*x) / 8.0
	}
	return fs[:n]
}

func getSystemOfExponentialFunctions(n int) []F {
	fs := make([]F, n)
	for i := 0; i < n; i++ {
		j := i
		fs[i] = func(x float64) float64 {
			return math.Pow(math.E, float64(j)*x)
		}
	}
	return fs
}

func getSystemOfPolynomicalFunctions(n int) []F {
	fs := make([]F, n)
	for i := 0; i < n; i++ {
		j := i
		fs[i] = func(x float64) float64 {
			return math.Pow(x, float64(j))
		}
	}
	return fs
}

func getFunction(k, c, w float64) F {
	return func(x float64) float64 {
		return k*math.Log(x) + c*math.Cos(w*x)
	}
}

func solve(left, right float64, f F, phis []F) []float64 {
	n := len(phis)
	m := make([]float64, n*n)
	b := make([]float64, n)
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			m[i*n+j] = scalarProduction(phis[i], phis[j], left, right)
		}
	}

	for i := 0; i < n; i++ {
		b[i] = scalarProduction(f, phis[i], left, right)
	}

	ctx := gauss.NewGaussContext(m, b)
	ctx.PrintState()
	ctx.Solve()
	ctx.PrintState()
	return ctx.GetAnswer()
}

type Task struct {
	A float64
	B float64
	N int
	K float64
	P float64
	C float64
	W float64
	M float64

	F    F
	Phis []F

	coeffs []float64
	q      F
}

func (t *Task) Solve() {
	t.coeffs = solve(t.A, t.B, t.F, t.Phis)

	t.q = func(x float64) float64 {
		sum := 0.0
		for i := 0; i <= t.N; i++ {
			sum += t.Phis[i](x) * t.coeffs[i]
		}
		return sum
	}
}

func (t *Task) GetDeviation() float64 {
	deviation := func(x float64) float64 {
		return (t.F(x) - t.q(x)) * (t.F(x) - t.q(x))
	}
	return integrate(deviation, t.A, t.B)
}

func (t *Task) GetExponentialFormula() string {
	eq := ""
	for i := 0; i <= t.N; i++ {
		eq += fmt.Sprintf(" + (%f)*(e^(%d*x))", t.coeffs[i], i)
	}
	return eq
}

func (t *Task) GetLegendreFormula() string {
	polynomials := []string{
		"(1)",
		"(x)",
		"(3*x^2-1)/2",
		"(5*x^3-3*x)/2",
		"(35*x^4-30*x^2+3)/8",
		"(63*x^5-70*x^3+15)/8",
	}[:t.N+1]
	eq := ""
	for i := 0; i <= t.N; i++ {
		eq += fmt.Sprintf(" + (%6.6f)*%s", t.coeffs[i], polynomials[i])
	}
	return eq
}

func (t *Task) GetPolynomsFormula() string {
	eq := ""
	for i := 0; i <= t.N; i++ {
		eq += fmt.Sprintf(" + (%6.6f)*(x^%d)", t.coeffs[i], i)
	}
	return eq
}
