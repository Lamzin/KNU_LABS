types          = ["int8", "int16", "int32", "int64", "float32", "float64"]
operations     = [["+", "addition"], ["-", "substract"], ["*", "multiplication"], ["/", "division"]]
source_file    = open("test.go", "w+")

init = {
    "int8" : "91, 23, 65, 55",
    "int16" : "10123, 9965, 4532, 1235",
    "int32" : "1073752832, 1073982652, 1065752, 45648989",
    "int64" : "6341068276411411200, 668276411411200, 634106456465964100, 4644848",

    "float32" : "464566.64654, 999566.685465, 465.45644978, 4599.99998",
    "float64" : "164545.11164645, 4641010566.101064654, 464566999.64659994, 4464564566.64654456456"
}



###########################################################
###########################################################
###########################################################
template_file  = open("template_main.go", "r+")
template       = ""

for line in template_file:
    template += line

source_file.write(template)


###########################################################
###########################################################
###########################################################

template_file  = open("template_run_func.go", "r+")
template       = ""

for line in template_file:
    template += line

for t in types: 
    template_new = template.replace("#TYPE", t)

    for i in range(4):
        template_new = template_new.replace("#OPERATION_%d" % (i + 1), operations[i][0])
        template_new = template_new.replace("#OPERATION_NAME_%d" % (i + 1), operations[i][1])

    source_file.write(template_new)



###########################################################
###########################################################
###########################################################

template_file  = open("template_func.go", "r+")
template       = ""

for line in template_file:
    template += line

for t in types:
    for op in operations:
        template_new = template.replace("#TYPE", t)
        template_new = template_new.replace("#OPERATION_NAME", op[1])
        template_new = template_new.replace("#OPERATION", op[0])
        template_new = template_new.replace("#INITIALISE_VARIABLES", init[t])
            


        source_file.write(template_new)
