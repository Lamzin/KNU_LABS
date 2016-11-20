package main

import (
	"fmt"
	"github.com/Lamzin/go.matrix"
	"math"
)

func main() {
	ctx := NewZeidelContext(GetInput())
	ctx.Normalize()
	ctx.PrintState()
	var i int
	for i = 0; ctx.Iteration(); i++ {
		ctx.PrintState()
	}
	fmt.Printf("%d iterations\n", i)
}

type ZeidelContext struct {
	N int
	M *matrix.DenseMatrix
	B *matrix.DenseMatrix
	X *matrix.DenseMatrix
}

func NewZeidelContext(mitems []float64, bitems []float64) ZeidelContext {
	m := matrix.MakeDenseMatrix(mitems, int(math.Sqrt(float64(len(mitems)))), int(math.Sqrt(float64(len(mitems)))))
	b := matrix.MakeDenseMatrix(bitems, len(bitems), 1)
	return ZeidelContext{
		N: len(bitems),
		M: matrix.ParallelProduct(m.Transpose(), m),
		B: matrix.ParallelProduct(m.Transpose(), b),
		X: matrix.MakeDenseMatrix(make([]float64, len(bitems)), len(bitems), 1),
	}
}

func (ctx *ZeidelContext) Normalize() {
	for i := 0; i < ctx.N; i++ {
		ii := ctx.M.Get(i, i)
		for j := 0; j < ctx.N; j++ {
			ij := ctx.M.Get(i, j)
			ctx.M.Set(i, j, ij/ii)
		}
		ctx.B.Set(i, 0, ctx.B.Get(i, 0)/ii)
	}
}

func (ctx *ZeidelContext) Iteration() bool {
	x := matrix.MakeDenseCopy(ctx.X)
	for i := 0; i < ctx.N; i++ {
		var xi float64 = ctx.B.Get(i, 0)
		for j := 0; j < ctx.N; j++ {
			if i != j {
				xi += x.Get(j, 0) * ctx.M.Get(i, j)
			}
		}
		x.Set(i, 0, -xi)
	}
	delta := getMaxDelta(x, ctx.X, ctx.N)
	ctx.X = x
	return delta > 0.000001
}

func (ctx *ZeidelContext) PrintState() {
	fmt.Printf("M:\n%s\n", ctx.M.String())
	fmt.Printf("B:\n%s\n", ctx.B.String())
	fmt.Printf("X:\n%s\n", ctx.X.String())
	fmt.Printf("\n")
}

func getMaxDelta(x *matrix.DenseMatrix, y *matrix.DenseMatrix, n int) (maxDelta float64) {
	maxDelta = 0
	for i := 0; i < n; i++ {
		maxDelta = math.Max(maxDelta, math.Abs(x.Get(i, 0)-y.Get(i, 0)))
	}
	return
}
