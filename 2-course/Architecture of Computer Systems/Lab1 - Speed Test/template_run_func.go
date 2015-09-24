
func test_run_#TYPE() {

    t_1 := test_#TYPE_#OPERATION_NAME_1()
    t_2 := test_#TYPE_#OPERATION_NAME_2()
    t_3 := test_#TYPE_#OPERATION_NAME_3()
    t_4 := test_#TYPE_#OPERATION_NAME_4()


    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "#OPERATION_1", "#TYPE", 1 / t_1 * 10.0, string_linear(t_1 * 25 / t_1), t_1 * 100 / t_1)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "#OPERATION_2", "#TYPE", 1 / t_2 * 10.0, string_linear(t_1 * 25 / t_2), t_1 * 100 / t_2)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "#OPERATION_3", "#TYPE", 1 / t_3 * 10.0, string_linear(t_1 * 25 / t_3), t_1 * 100 / t_3)
    fmt.Printf("%s | %8s | %8.3fM | %35s | %8.3f%% \n",  "#OPERATION_4", "#TYPE", 1 / t_4 * 10.0, string_linear(t_1 * 25 / t_4), t_1 * 100 / t_4)
    fmt.Printf("\n")

}

