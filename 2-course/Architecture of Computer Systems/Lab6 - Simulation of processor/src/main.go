package main


import (
	"strings"
	"os"
	"./command"
	"./functions"
	"./processor"
)


func main(){
	proc := processor.NewProcessor()
	commands := command.GetCommands()
	processing := map[string] func (*processor.Processor, *command.Command){
		"add" 	: functions.Add,
		"sub" 	: functions.Sub,
		"mul"	: functions.Mul,
		"div"	: functions.Div,
		"bswp" 	: functions.BitsSwap,
		"copy"	: functions.Copy,
	}

	
	var ch []byte = make([]byte, 2)
	for i, command := range commands {
		os.Stdin.Read(ch)

		proc.IR = strings.Join([]string{command.Name, command.Operand1, command.Operand2}, " ")
		proc.PC = int32(i + 1)
		proc.TC = 1
		proc.Watch()


		if fn, ok := processing[command.Name]; ok {
			fn(&proc, &command)
		} else {
			panic("Command not found!")
		}


		os.Stdin.Read(ch)

		proc.PS = functions.Signum(proc.Variables[command.Operand1])
		proc.TC = 2
		proc.Watch()
	}

}