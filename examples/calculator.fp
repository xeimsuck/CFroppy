println("## Welcome to calculator! ##\n");

loop {
    print("Input first number: ");
    let first = to_decimal(input());
    if(!is_instance(first, "decimal")) {
        eprint("Incorrect number");
        return 1;
    }

    print("Input second number: ");
    let second = to_decimal(input());
    if(!is_instance(second, "decimal")) {
        eprint("Incorrect number");
        return 1;
    }

    print("Input operator (+, -, *, =): ");
    let oper = input();
    if(oper=="+") {
        println(format("Answer: ", first+second));
    } else if(oper=="-"){
        println(format("Answer: ", first-second));
    } else if(oper=="/"){
        println(format("Answer: ", first/second));
    } else if(oper=="*"){
        println(format("Answer: ", first*second));
    } else {
        eprint("Incorrect operator");
        return 1;
    }

    println("");
}

