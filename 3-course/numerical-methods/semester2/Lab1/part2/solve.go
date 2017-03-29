package main

import (
	"fmt"
	"math"

	"../gauss"
	"github.com/Lamzin/go.matrix"
	"io/ioutil"
	"strings"
)

func main() {
	t := Task{
		N: 4,
		A: 1.0,
		B: 3.0,
		K: 1.0,
		C: 1.0,
		W: 9,
		M: 20.0,
	}
	t.F = func(x float64) float64 {
		return t.K*math.Log(x) + t.C*math.Cos(t.W*x)
	}

	fmt.Println(t.GetOriginFormula())

	report := fmt.Sprintf(
		"%6.6f\n%6.6f\n%s\n%s\n%s\n%s\n",
		t.A,
		t.B,
		t.GetOriginFormula(),
		solveLegendre(t),
		solveExponential(t),
		solveSpline(t),
	)

	ioutil.WriteFile("expressions.txt", []byte(report), 0644)
}

func solveExponential(t Task) string {
	t.Phis = func(n int) []F {
		fs := make([]F, n)
		for i := 0; i < n; i++ {
			j := i
			fs[i] = func(x float64) float64 {
				return math.Pow(math.E, float64(j)*x)
			}
		}
		return fs
	}(t.N + 1)

	t.Solve()

	fmt.Println("\nExponential:")
	fmt.Println(t.GetExponentialFormula())
	fmt.Printf("Deviation: %6.6f\n", t.GetDeviation())

	return t.GetExponentialFormula()
}

func solveLegendre(t Task) string {
	t.Phis = []F{
		func(x float64) float64 { return 1 },
		func(x float64) float64 { return x },
		func(x float64) float64 { return (3.0*x*x - 1) / 2.0 },
		func(x float64) float64 { return (5.0*x*x*x - 3.0*x) / 2.0 },
		func(x float64) float64 { return (35.0*x*x*x*x - 30.0*x*x + 3) / 8.0 },
		func(x float64) float64 { return (63.0*x*x*x*x*x - 70.0*x*x*x + 15.0*x) / 8.0 },
	}[:t.N+1]
	for i := 0; i < len(t.Phis); i++ {
		t.Phis[i] = func(f F) F {
			return func(x float64) float64 {
				return f((2*x - t.A - t.B) / (t.B - t.A))
			}
		}(t.Phis[i])
	}

	t.Solve()

	fmt.Println("\nLegendre:")
	fmt.Println(t.GetLegendreFormula())
	fmt.Printf("Deviation: %6.6f\n", t.GetDeviation())

	return t.GetLegendreFormula()
}

func solveSpline(t Task) string {
	n := int(t.M)
	h := (t.B - t.A) / t.M

	xitems := make([]float64, n+1)
	for i := 0; i < n+1; i++ {
		xitems[i] = t.A + h*float64(i)
	}

	aitems := make([]float64, (n-1)*(n-1))
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-1; j++ {
			if i == j {
				aitems[i*(n-1)+j] = 2.0 * h / 3.0
			} else if i == j+1 || i+1 == j {
				aitems[i*(n-1)+j] = h / 6.0
			} else {
				aitems[i*(n-1)+j] = 0
			}
		}
	}
	A := matrix.MakeDenseMatrix(aitems, n-1, n-1)

	hitems := make([]float64, (n-1)*(n+1))
	for i := 0; i < n-1; i++ {
		for j := 0; j < n+1; j++ {
			if i == j {
				hitems[i*(n+1)+j] = 1.0 / h
			} else if i+1 == j {
				hitems[i*(n+1)+j] = -2.0 / h
			} else if i+2 == j {
				hitems[i*(n+1)+j] = 1.0 / h
			} else {
				hitems[i*(n+1)+j] = 0
			}
		}
	}
	H := matrix.MakeDenseMatrix(hitems, n-1, n+1)

	pitems := make([]float64, (n+1)*(n+1))
	for i := 0; i < n+1; i++ {
		for j := 0; j < n+1; j++ {
			if i == j {
				pitems[i*(n+1)+j] = 1 / 1000.0
			} else {
				pitems[i*(n+1)+j] = 0
			}
		}
	}
	P := matrix.MakeDenseMatrix(pitems, n+1, n+1)

	fitems := make([]float64, (n+1)*(1))
	for i := 0; i < n+1; i++ {
		fitems[i] = t.F(xitems[i])
	}
	F := matrix.MakeDenseMatrix(fitems, n+1, 1)

	LEFT := matrix.Sum(matrix.Product(H, P, matrix.Transpose(H)), A)
	RIGHT := matrix.Product(H, F)

	order := make([]int, n-1)
	for i := 0; i < n-1; i++ {
		order[i] = i
	}
	gctx := gauss.GaussContext{
		N:     n - 1,
		M:     LEFT,
		B:     RIGHT,
		Order: order,
	}
	gctx.Solve()
	mitems := gctx.GetAnswer()
	M := matrix.MakeDenseMatrix(mitems, n-1, 1)

	MU := matrix.Difference(F, matrix.Product(P, matrix.Transpose(H), M))
	muitems := make([]float64, n+1)
	for i := 0; i < n+1; i++ {
		muitems[i] = MU.Get(i, 0)
	}

	// add 0th and (n)th value to mitems
	mitems = append([]float64{0.0}, mitems...)
	mitems = append(mitems, 0.0)

	response := fmt.Sprintf("%d\n", n)
	for i := 1; i < n+1; i++ {
		response += fmt.Sprintf("%.8f\n%.8f\n", xitems[i-1], xitems[i])
		response += fmt.Sprintf(
			"(%.8f)*((%.8f) - x)^3 + (%.8f)*(x - (%.8f))^3 + (%.8f)*((%.8f) - x) + (%.8f)*(x - (%.8f))\n",
			mitems[i-1]/6/h,
			xitems[i],
			mitems[i]/6/h,
			xitems[i-1],
			(muitems[i-1]-mitems[i-1]*h*h/6.0)/h,
			xitems[i],
			(muitems[i]-mitems[i]*h*h/6.0)/h,
			xitems[i-1],
		)
	}
	return response
}

type F func(float64) float64

func integrate(f F, a float64, b, m float64) (I float64) {
	if a > b {
		panic("a > b")
	}
	delta := (b - a) / m
	for ; a < b; a += delta {
		I += f(a)
	}
	return
}

func scalarProduction(f, g F, a, b, m float64) float64 {
	h := func(x float64) float64 {
		return f(x) * g(x)
	}
	return integrate(h, a, b, m)
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

func solve(left, right, pointCnt float64, f F, phis []F) []float64 {
	n := len(phis)
	m := make([]float64, n*n)
	b := make([]float64, n)
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			m[i*n+j] = scalarProduction(phis[i], phis[j], left, right, pointCnt)
		}
	}

	for i := 0; i < n; i++ {
		b[i] = scalarProduction(f, phis[i], left, right, pointCnt)
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
	t.coeffs = solve(t.A, t.B, t.M, t.F, t.Phis)
	fmt.Println(t.coeffs)

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
	return math.Sqrt(integrate(deviation, t.A, t.B, t.M))
}

func (t *Task) GetOriginFormula() string {
	return fmt.Sprintf("%f * log(x) + %f * cos(%f * x)", t.K, t.C, t.W)
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

	replace := fmt.Sprintf("((2 * x - %6.6f)/%6.6f)", t.A+t.B, t.B-t.A)
	for i := 0; i < len(polynomials); i++ {
		polynomials[i] = strings.Replace(polynomials[i], "x", replace, -1)
	}

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
