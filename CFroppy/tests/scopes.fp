var a = "global";
var b = "global";
var c = "global";

{
    var a = "local-1";
    var b = "local-1";
    {
        var a = "local-2";

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