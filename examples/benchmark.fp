print("Input a count of iterations: ");
let count = to_integer(input());
if(!is_instance(count, "integer")) {
    eprint("Count must be number");
    return 1;
}

let start = clock();

for(let i = 0; i < count; i+=1) {
}

let end = clock();

println(format("Time: ", duration(start, end), "ms"));
