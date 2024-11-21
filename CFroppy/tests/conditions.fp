var x = to_integer(input());

/// if(x===nil) {
///     eprint("x is not integer"); // error: x must be integer
/// }

if(x<0) {
    println("x less than 0");
} else if(x>0) {
    println("x greater than 0");
} else {
    println("x equal 0");
}