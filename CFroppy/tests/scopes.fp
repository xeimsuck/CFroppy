let a = "global";
let b = "global";
let c = "global";

{
    let a = "local-1";
    let b = "local-1";
    {
        let a = "local-2";

        println (a);
        println (b);
        println (c);
    }

    println (a);
    println (b);
    println (c);
}

println(a);
println(b);
println(c);