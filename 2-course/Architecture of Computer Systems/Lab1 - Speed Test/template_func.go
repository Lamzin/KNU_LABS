
func test_#TYPE_#OPERATION_NAME() float64 {
    var a, b, c, d #TYPE = #INITIALISE_VARIABLES


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
        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

        d = a #OPERATION b
        d = b #OPERATION c
        d = c #OPERATION a
        d = d #OPERATION a

    }
    end_2 := time.Since(begin_2)

    a = d
    d = b
    b = c
    c = a

    return end_2.Seconds() - end_1.Seconds()
}

