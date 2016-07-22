package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	answer := 0
	matrix := in()

	used := make(map[int]struct{}, 0)

	prev := 0
	used[prev] = struct{}{}
	for len(used) < len(matrix) {
		nextIndex := 1000
		nextValue := 1000
		for i, _ := range matrix {
			if _, ok := used[i]; ok {
				continue
			}
			if matrix[prev][i] < nextValue {
				nextIndex = i
				nextValue = matrix[prev][i]
			}
		}
		used[nextIndex] = struct{}{}
		prev = nextIndex
		answer += nextValue
	}
	answer += matrix[prev][0]

	out(answer)
}

func in() (matrix [][]int) {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		matrix = append(matrix, make([]int, 0))
		strSlice := strings.Split(scanner.Text(), " ")
		for _, str := range strSlice {
			i, err := strconv.Atoi(str)
			if err != nil {
				log.Fatal(err)
			}
			matrix[len(matrix)-1] = append(matrix[len(matrix)-1], i)
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	if len(matrix) == 0 {
		log.Fatal("empty file")
	}

	for _, line := range matrix {
		if len(line) != len(matrix[0]) {
			log.Fatal("not matrix")
		}
	}

	if len(matrix) != len(matrix[0]) {
		log.Fatal("not matrix")
	}

	return
}

func out(answer int) {
	file, err := os.OpenFile("output.txt", os.O_RDWR, 0660)
	defer file.Close()

	if err != nil {
		log.Fatal(err)
	}

	_, err = file.Write([]byte(fmt.Sprintf("%d\n", answer)))
	if err != nil {
		log.Fatal(err)
	}
}
