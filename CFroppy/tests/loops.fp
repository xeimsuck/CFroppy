let x = 0;
while(x < 5) {
    println(format("while: x = ", x));
    x+=1;
}

for(let i = 0; i < 5; i+=1) {
    println(format("for: i = ", i));
}

let z = 0;
while(true) {
    if(z+=1 == 5) break;
    println(format("while (break): z = ", z));
}