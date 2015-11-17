package command


import (
	"io/ioutil"
	"strings"
)

 
type Command struct {
	Name, Operand1, Operand2 string
}


func NewCommand(name, operand1, operand2 string) Command{
	var command Command
	command.Name 		= name
	command.Operand1 	= operand1
	command.Operand2 	= operand2
	return command
}


func GetCommands() []Command{
	var commands []Command
	input, err := ioutil.ReadFile("input")
	
	if err != nil{
		panic("#Error: problems with input file.")
	}

	for _, line := range strings.Split(string(input), "\r\n"){
		if arr := strings.Split(line, " "); len(arr) == 3 {
			commands = append(commands, NewCommand(arr[0], arr[1], arr[2]))
		} else {
			panic("#Error: line not contain 3 operands")
		}
	}

	return commands
}