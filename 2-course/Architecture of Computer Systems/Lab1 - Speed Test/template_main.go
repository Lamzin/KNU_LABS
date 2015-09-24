package main


import "fmt"
import "time"


func main(){

    test_run_int8()
    test_run_int16()
    test_run_int32()
    test_run_int64()

    test_run_float32()
    test_run_float64()

}


func string_linear(x float64) string{
    result := ""
    for i := 0; i < int(x); i++{
        result += "*"
    }

    return result
}