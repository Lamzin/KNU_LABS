package main

import (
	"fmt"
	"github.com/Lamzin/go.matrix"
	"math"
)

type matrixContext struct {
	M          *matrix.DenseMatrix
	N          int
	CondNumber float64
}

func main() {
	ctx := NewMatrix(GetInput())
	ctx.CalculateConditionalityNumber()
	ctx.PrintState()
}

func NewMatrix(mitems []float64, _ []float64) matrixContext {
	m := matrix.MakeDenseMatrix(mitems, int(math.Sqrt(float64(len(mitems)))), int(math.Sqrt(float64(len(mitems)))))
	return matrixContext{M: m, N: int(math.Sqrt(float64(len(mitems))))}
}

func (ctx *matrixContext) CalculateConditionalityNumber() {
	mInverse, _ := ctx.M.Inverse()
	ctx.CondNumber = GetNorm(ctx.M, ctx.N) * GetNorm(mInverse, ctx.N)
}

func (ctx *matrixContext) PrintState() {
	mInverse, _ := ctx.M.Inverse()
	fmt.Printf("M:\n%s\n", ctx.M.String())
	fmt.Printf("inverse matrix:\n%s\n", mInverse.String())
	fmt.Printf("conditionality number: %f\n", ctx.CondNumber)
	fmt.Printf("\n")
}

func GetNorm(m *matrix.DenseMatrix, n int) (norm float64) {
	for i := 0; i < n; i++ {
		var sum float64
		for j := 0; j < n; j++ {
			sum += math.Abs(m.Get(i, j))
		}
		if i == 0 || sum > norm {
			norm = sum
		}
	}
	return
}
