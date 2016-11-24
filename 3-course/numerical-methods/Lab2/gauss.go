package main

import (
	"fmt"
	"github.com/Lamzin/go.matrix"
	"math"
)

func main() {
	ctx := NewGaussContext(GetInput())
	ctx.Solve()
	ctx.PrintState()
}

type GaussContext struct {
	N     int
	M     *matrix.DenseMatrix
	B     *matrix.DenseMatrix
	Order []int
}

func NewGaussContext(mitems []float64, bitems []float64) GaussContext {
	m := matrix.MakeDenseMatrix(mitems, int(math.Sqrt(float64(len(mitems)))), int(math.Sqrt(float64(len(mitems)))))
	b := matrix.MakeDenseMatrix(bitems, len(bitems), 1)
	order := make([]int, len(bitems))
	for i := 0; i < len(bitems); i++ {
		order[i] = i
	}
	return GaussContext{
		N:     len(bitems),
		M:     m,
		B:     b,
		Order: order,
	}
}

func (ctx *GaussContext) Solve() {
	for i := 0; i < ctx.N; i++ {
		maxIndex := i
		maxValue := ctx.M.Get(i, maxIndex)
		for j := i + 1; j < ctx.N; j++ {
			if math.Abs(maxValue) < math.Abs(ctx.M.Get(i, j)) {
				maxIndex = j
				maxValue = ctx.M.Get(i, j)
			}
		}
		ctx.swapColumns(i, maxIndex)

		for j := 0; j < ctx.N; j++ {
			ctx.M.Set(i, j, ctx.M.Get(i, j)/maxValue)
		}
		ctx.B.Set(i, 0, ctx.B.Get(i, 0)/maxValue)

		for ii := 0; ii < ctx.N; ii++ {
			if i == ii {
				continue
			}
			k := ctx.M.Get(ii, i)
			for jj := 0; jj < ctx.N; jj++ {
				ctx.M.Set(ii, jj, ctx.M.Get(ii, jj)-k*ctx.M.Get(i, jj))
			}
			ctx.B.Set(ii, 0, ctx.B.Get(ii, 0)-k*ctx.B.Get(i, 0))
		}
	}
}

func (ctx *GaussContext) swapColumns(i, j int) {
	ctx.Order[i], ctx.Order[j] = ctx.Order[j], ctx.Order[i]
	for index := 0; index < ctx.N; index++ {
		tmp := ctx.M.Get(index, i)
		ctx.M.Set(index, i, ctx.M.Get(index, j))
		ctx.M.Set(index, j, tmp)
	}
}

func (ctx *GaussContext) PrintState() {
	fmt.Printf("M:\n%s\n", ctx.M.String())
	fmt.Printf("B:\n%s\n", ctx.B.String())
	fmt.Printf("Order:\n%x\n", ctx.Order)
	fmt.Printf("\n")
}
