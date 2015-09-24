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
func test_run_int8() {

    t_1 := test_int8_addition()
    t_2 := test_int8_substract()
    t_3 := test_int8_multiplication()
    t_4 := test_int8_division()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "+", "int8", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "-", "int8", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "*", "int8", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "/", "int8", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}


func test_run_int16() {

    t_1 := test_int16_addition()
    t_2 := test_int16_substract()
    t_3 := test_int16_multiplication()
    t_4 := test_int16_division()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "+", "int16", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "-", "int16", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "*", "int16", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "/", "int16", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}


func test_run_int32() {

    t_1 := test_int32_addition()
    t_2 := test_int32_substract()
    t_3 := test_int32_multiplication()
    t_4 := test_int32_division()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "+", "int32", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "-", "int32", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "*", "int32", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "/", "int32", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}


func test_run_int64() {

    t_1 := test_int64_addition()
    t_2 := test_int64_substract()
    t_3 := test_int64_multiplication()
    t_4 := test_int64_division()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "+", "int64", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "-", "int64", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "*", "int64", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "/", "int64", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}


func test_run_float32() {

    t_1 := test_float32_addition()
    t_2 := test_float32_substract()
    t_3 := test_float32_multiplication()
    t_4 := test_float32_division()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "+", "float32", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "-", "float32", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "*", "float32", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "/", "float32", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}


func test_run_float64() {

    t_1 := test_float64_addition()
    t_2 := test_float64_substract()
    t_3 := test_float64_multiplication()
    t_4 := test_float64_division()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "+", "float64", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "-", "float64", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "*", "float64", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "/", "float64", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}


func test_int8_addition() float64 {
    var a, b, c, d int8 = 91, 23, 65, 55


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int8_substract() float64 {
    var a, b, c, d int8 = 91, 23, 65, 55


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int8_multiplication() float64 {
    var a, b, c, d int8 = 91, 23, 65, 55


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int8_division() float64 {
    var a, b, c, d int8 = 91, 23, 65, 55


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int16_addition() float64 {
    var a, b, c, d int16 = 10123, 9965, 4532, 1235


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int16_substract() float64 {
    var a, b, c, d int16 = 10123, 9965, 4532, 1235


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int16_multiplication() float64 {
    var a, b, c, d int16 = 10123, 9965, 4532, 1235


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int16_division() float64 {
    var a, b, c, d int16 = 10123, 9965, 4532, 1235


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int32_addition() float64 {
    var a, b, c, d int32 = 1073752832, 1073982652, 1065752, 45648989


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int32_substract() float64 {
    var a, b, c, d int32 = 1073752832, 1073982652, 1065752, 45648989


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int32_multiplication() float64 {
    var a, b, c, d int32 = 1073752832, 1073982652, 1065752, 45648989


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int32_division() float64 {
    var a, b, c, d int32 = 1073752832, 1073982652, 1065752, 45648989


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int64_addition() float64 {
    var a, b, c, d int64 = 6341068276411411200, 668276411411200, 634106456465964100, 4644848


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int64_substract() float64 {
    var a, b, c, d int64 = 6341068276411411200, 668276411411200, 634106456465964100, 4644848


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int64_multiplication() float64 {
    var a, b, c, d int64 = 6341068276411411200, 668276411411200, 634106456465964100, 4644848


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_int64_division() float64 {
    var a, b, c, d int64 = 6341068276411411200, 668276411411200, 634106456465964100, 4644848


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float32_addition() float64 {
    var a, b, c, d float32 = 464566.64654, 999566.685465, 465.45644978, 4599.99998


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float32_substract() float64 {
    var a, b, c, d float32 = 464566.64654, 999566.685465, 465.45644978, 4599.99998


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float32_multiplication() float64 {
    var a, b, c, d float32 = 464566.64654, 999566.685465, 465.45644978, 4599.99998


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float32_division() float64 {
    var a, b, c, d float32 = 464566.64654, 999566.685465, 465.45644978, 4599.99998


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float64_addition() float64 {
    var a, b, c, d float64 = 164545.11164645, 4641010566.101064654, 464566999.64659994, 4464564566.64654456456


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

        d = a + b
        d = b + c
        d = c + a
        d = d + a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float64_substract() float64 {
    var a, b, c, d float64 = 164545.11164645, 4641010566.101064654, 464566999.64659994, 4464564566.64654456456


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

        d = a - b
        d = b - c
        d = c - a
        d = d - a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float64_multiplication() float64 {
    var a, b, c, d float64 = 164545.11164645, 4641010566.101064654, 464566999.64659994, 4464564566.64654456456


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

        d = a * b
        d = b * c
        d = c * a
        d = d * a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}


func test_float64_division() float64 {
    var a, b, c, d float64 = 164545.11164645, 4641010566.101064654, 464566999.64659994, 4464564566.64654456456


    begin_1 := time.Now()
    for i := 0; i < 10000000; i++ {
        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a

        b = a
        a = c
        c = b
        d = a
    }
    end_1 := time.Since(begin_1);


    begin_2 := time.Now()
    for i := 0; i < 10000000; i++ {
        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

        d = a / b
        d = b / c
        d = c / a
        d = d / a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}

