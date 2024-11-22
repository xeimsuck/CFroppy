println("!Guess the number!");

// get min
print("Input a minimal possible number: ");
let min = to_integer(input());
if(!is_instance(min, "integer")) {
    eprint("Minimum must be integer");
    return 1;
}

// get max
print("Input a maximum possible number: ");
let max = to_integer(input());
if(!is_instance(min, "integer")) {
    eprint("Maximum must be integer");
    return 1;
}

let number = rand(min, max);
println("Number is generated. Try to guess it!");

loop {
    print("Input your guess: ");
    let attempt = to_integer(input());

    if(attempt<number) println(format(attempt, " is less than guessed number."));
    else if(attempt>number) println(format(attempt, " is greater than guessed number."));
    else break;
}

println("Great! You guessed it!");