package processor


import "fmt"


type Processor struct {
	IR 			string
	R1, R2 		int64
	PS, PC, TC 	int32
	Variables 	map[string]int64
}


func NewProcessor() Processor {
	var proc Processor
	proc.Variables  		= make(map[string]int64)
	proc.Variables["R1"] 	= 0
	proc.Variables["R2"] 	= 0
	return proc
}


func BitRepresent(R int64) string {
	var last, pow int64 = 0, 134217728 // 0, 2 ** 27
	var s string

	if R < 0 {
		last = 1
	}

	if last != R & (1 << 26) {
		R = R ^ (1 << 26)
	}

	for i := 27; i>=0; i-- {
		if R & pow > 0 {
			s += "1"
		} else {
			s += "0"
		}

		if i % 4 == 0 {
			s += " "
		}

		pow /= 2
	}

	return s
}


func (s Processor) Watch() {
	fmt.Println("IR: ", s.IR)
	fmt.Println("R1: ", BitRepresent(s.Variables["R1"]))
	fmt.Println("R2: ", BitRepresent(s.Variables["R2"]))
	fmt.Println("PS: ", s.PS)
	fmt.Println("PC: ", s.PC)
	fmt.Println("TC: ", s.TC)
	fmt.Println()
}