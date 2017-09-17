package main

import (
	"fmt"
	"github.com/Lamzin/go.matrix"
	"io/ioutil"
	"math"
)

type Config struct {
	A float64
	B float64
	C float64
	D float64
	K float64
	N float64
	L float64
}

type F func(x float64) float64

type Y func(x float64, y *matrix.DenseMatrix) *matrix.DenseMatrix

type Task struct {
	Config        Config
	N             int
	f             F
	StartValues   *matrix.DenseMatrix
	System        Y
	ExactSolution F
}

func (t *Task) Init() {
	t.f = func(x float64) float64 {
		c := t.Config
		return math.Pow(c.A, 3)*math.Pow(math.E, c.A*x) +
			c.K*x*c.A*c.A*math.Pow(math.E, c.A*x) +
			2*c.K*c.B*x +
			math.Pow(c.A*math.Pow(math.E, c.A*x)+2*c.B*x+c.C, 2) +
			c.N*math.Pow(math.E, c.A*x) +
			c.N*c.B*x*x +
			c.N*c.C*x +
			c.N*c.D
	}

	t.StartValues = matrix.MakeDenseMatrix([]float64{
		1 + t.Config.D,
		t.Config.A + t.Config.C,
		math.Pow(t.Config.A, 2) + 2*t.Config.B,
	}, 3, 1)

	t.System = func(x float64, y *matrix.DenseMatrix) *matrix.DenseMatrix {
		return matrix.MakeDenseMatrix([]float64{
			y.Get(1, 0),
			y.Get(2, 0),
			t.f(x) - t.Config.K*x*y.Get(2, 0) - math.Pow(y.Get(1, 0), 2) - t.Config.N*y.Get(0, 0),
		}, 3, 1)
	}

	t.ExactSolution = func(x float64) float64 {
		return math.Pow(math.E, t.Config.A*x) + t.Config.B*x*x + t.Config.C*x + t.Config.D
	}
}

func (t *Task) Solve() {
	h := t.Config.L / float64(t.N)

	y := t.StartValues
	all := []*matrix.DenseMatrix{y}
	for x := 0.0; x <= t.Config.L; x += h {
		H := matrix.MakeDenseMatrix([]float64{h}, 1, 1)
		H2 := matrix.MakeDenseMatrix([]float64{h / 2}, 1, 1)
		H6 := matrix.MakeDenseMatrix([]float64{h / 6}, 1, 1)

		k1 := t.System(x, y)
		k2 := t.System(x+h/2, matrix.Sum(y, matrix.Product(k1, H2)))
		k3 := t.System(x+h/2, matrix.Sum(y, matrix.Product(k2, H2)))
		k4 := t.System(x+h, matrix.Sum(y, matrix.Product(k3, H)))

		ksum := matrix.Sum(k1, k2, k2, k3, k3, k4)
		ksum = matrix.Product(ksum, H6)
		y = matrix.Sum(y, ksum)
		all = append(all, y)
	}

	fmt.Println("x              exact          approximation  delta")
	for i, item := range all {
		x := h * float64(i)
		exact := t.ExactSolution(x)
		approximation := (*item).Get(0, 0)
		fmt.Printf(
			"%.8f     %.8f     %.8f     %.8f\n",
			x, exact, approximation, math.Abs(exact-approximation))
	}

	l1 := ""
	l2 := ""
	for i, item := range all {
		x := h * float64(i)
		exact := t.ExactSolution(x)
		approximation := (*item).Get(0, 0)

		l1 += fmt.Sprintf("%.8f %.8f ", x, exact)
		l2 += fmt.Sprintf("%.8f %.8f ", x, approximation)
	}
	report := l1 + "\n" + l2
	ioutil.WriteFile("expressions.txt", []byte(report), 0644)
}

func main() {
	t := Task{
		Config: Config{
			A: 3,
			B: 1,
			C: 1,
			D: 2,
			K: -2,
			N: -1,
			L: 1,
		},
		N: 20,
	}
	t.Init()
	t.Solve()
}
