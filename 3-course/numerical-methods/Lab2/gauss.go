package main

import (
	"fmt"
	"github.com/Lamzin/go.matrix"
	"math"
)

func main() {
	ctx := NewGaussContext(GetInput())
	ctx.Solve()
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
		maxValue := math.Abs(ctx.M.Get(i, maxIndex))
		for j := i; j < ctx.N; j++ {
			if maxValue < math.Abs(ctx.M.Get(i, j)) {
				maxIndex = j
				maxValue = math.Abs(ctx.M.Get(i, j))
			}
		}
		ctx.swapColumns(i, maxIndex)

		// TODO
		// miss understanding
	}
}

func (ctx *GaussContext) swapColumns(i, j int) {
	ctx.Order[i], ctx.Order[j] = ctx.Order[j], ctx.Order[i]

	tmp := ctx.B.Get(i, 0)
	ctx.B.Set(i, 0, ctx.B.Get(j, 0))
	ctx.B.Set(j, 0, tmp)

	for index := 0; index < ctx.N; index++ {
		tmp := ctx.M.Get(index, i)
		ctx.M.Set(index, i, ctx.M.Get(index, j))
		ctx.M.Set(index, j, tmp)
	}
}

func (ctx *GaussContext) PrintState() {
	fmt.Printf("M:\n%s\n", ctx.M.String())
	fmt.Printf("B:\n%s\n", ctx.B.String())
	fmt.Printf("\n")
}
