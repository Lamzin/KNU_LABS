package functions


import (
	"./../processor"
	"./../command"
	"strconv"
)


func GetOperands(proc *processor.Processor, command *command.Command) (write_to string, left, right int64) {
	write_to = command.Operand1
	
	if _, ok := proc.Variables[write_to]; !ok {
		proc.Variables[write_to] = 0
	}

	left = proc.Variables[write_to]

	if value, err := strconv.Atoi(command.Operand2); err != nil {
		if val, ok := proc.Variables[command.Operand2]; !ok {
			panic("Item doesn't exist.")
		} else {
			right = val
		}
	} else {
		right = int64(value)
	}

	return
}


func Signum(n int64) (m int32) {
	if n < 0 {
		m = -1
	} else if n > 0 {
		m = 1
	} else {
		m = 0
	}
	return m
}


func Add(proc *processor.Processor, command *command.Command) {
	write_to, value_left, value_right := GetOperands(proc, command)
	proc.Variables[write_to] = value_left + value_right
}


func Sub(proc *processor.Processor, command *command.Command) {
	write_to, value_left, value_right := GetOperands(proc, command)
	proc.Variables[write_to] = value_left - value_right
}


func Mul(proc *processor.Processor, command *command.Command) {
	write_to, value_left, value_right := GetOperands(proc, command)
	proc.Variables[write_to] = value_left * value_right
}


func Div(proc *processor.Processor, command *command.Command) {
	write_to, value_left, value_right := GetOperands(proc, command)
	if value_right == 0 {
		panic("Division by zero!")
	}
	proc.Variables[write_to] = value_left / value_right
}


func BitsSwap(proc *processor.Processor, command *command.Command) {
	if len(command.Operand2) != 4 {
		panic("Invalid operand!")
	}

	write_to, value_left, _ := GetOperands(proc, command)
	
	n := uint((int(command.Operand2[0]) - 48) * 10 + (int(command.Operand2[1]) - 48))
	m := uint((int(command.Operand2[2]) - 48) * 10 + (int(command.Operand2[3]) - 48))

	var nbit, mbit bool = value_left & (1 << n) > 0, value_left & (1 << m) > 0
	if n > 27 || m > 27 {
		panic("Invalid operand!")
	} else if nbit != mbit {
		value_left = value_left ^ (1 << n)
		value_left = value_left ^ (1 << m)
	}

	proc.Variables[write_to] = value_left
}


func Copy(proc *processor.Processor, command *command.Command) {
	write_to, _, value_right := GetOperands(proc, command)
	proc.Variables[write_to] = value_right
}