package main

import (
	"fmt"
	"math"
)

type F func(x float64) float64

type Integral struct {
	F F
	L float64
	R float64
}

func NewIntegral(f F, l, r float64) Integral {
	return Integral{
		F: f,
		L: l,
		R: r,
	}
}

func (i Integral) Calc(l, r float64) float64 {
	return i.F((l+r)/2.0) * (r - l)
}

func setupFormula(n float64) F {
	return func(x float64) float64 {
		return math.Pow(x, n) / math.Sqrt(1-x*x)
	}
}

type Task struct {
	I                  Integral
	Precision          float64
	AlgebraicPrecision float64

	points          []float64
	itetations      int
	ifinal, ih, ih2 float64
}

func (t Task) Solve() {
	t.points = []float64{t.I.L, t.I.R}

Loop:
	for ; ; t.itetations++ {
		t.PrintState()
		t.ih, t.ih2 = 0, 0
		newPoints := make([]float64, 0)

		for i := 1; i < len(t.points); i++ {
			l, r := t.points[i-1], t.points[i]
			IH := t.I.Calc(l, r)
			IH2 := t.I.Calc(l, (l+r)/2) + t.I.Calc((l+r)/2, r)
			R := math.Abs(IH2-IH) / (math.Pow(2, t.AlgebraicPrecision) - 1)

			newPoints = append(newPoints, l)
			if R > t.Precision / 2 {
				newPoints = append(newPoints, (l+r)/2.0)
			}
			t.ih += IH
			t.ih2 += IH2
		}
		newPoints = append(newPoints, t.I.R)

		if len(newPoints) == len(t.points) {
			break Loop
		}
		t.points = newPoints
	}
	t.PrintState()
	t.Richardson()
}

func (t Task) PrintState() {
	minDiff := t.I.R - t.I.L
	diff := make([]float64, len(t.points)-1)
	for i := 0; i < len(t.points)-1; i++ {
		diff[i] = t.points[i+1] - t.points[i]
		if diff[i] < minDiff {
			minDiff = diff[i]
		}
	}

	format := `Iteration #%d
points: %d, IH: %0.8f, IH2: %0.8f, eps: %0.8f
points array: %v
diff array: %v
min diff: %.8f
precision(by Runge): %.8f

`
	precision := (t.ih2 - t.ih) / (math.Pow(2, t.AlgebraicPrecision) - 1)
	fmt.Printf(format, t.itetations, len(t.points), t.ih, t.ih2, t.Precision, t.points, diff, minDiff, precision)
}

func (t Task) Richardson() {
	t.ifinal = (math.Pow(2, t.AlgebraicPrecision)*t.ih2 - t.ih) / (math.Pow(2, t.AlgebraicPrecision) - 1)

	fmt.Printf("final value: %.8f\n", t.ifinal)
}

func main() {

	t := Task{
		I:                  NewIntegral(setupFormula(2), 0, 1),
		Precision:          0.00001,
		AlgebraicPrecision: 2,
	}

	t.Solve()
}
