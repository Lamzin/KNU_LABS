package main

func GetInput() (mitems []float64, bitems []float64) {
	//3.6x1 + 1.8x2 - 4.7x3 = 3.8
	//2.7x1 - 3.6x2 + 1.9x3 = 0.4
	//1.5x1 + 4.5x2 + 3.3x3 = -1.6
	return []float64{
			3.6, 1.8, -4.7,
			2.7, -3.6, 1.9,
			1.5, 4.5, 3.3,
		},
		[]float64{
			3.8,
			0.4,
			-1.6,
		}
}

func GetInput2() (mitems []float64, bitems []float64) {
	return []float64{
			1, 2,
			1, 1,
		},
		[]float64{
			5,
			7,
		}
}

func GetInput3() (mitems []float64, bitems []float64) {
	return []float64{
			10, 1, 1,
			2, 10, 1,
			2, 2, 10,
		},
		[]float64{
			12,
			13,
			14,
		}
}
