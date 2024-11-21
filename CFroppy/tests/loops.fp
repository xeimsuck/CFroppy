var x = 0;
while(x < 5) {
    print format("while: x = ", x);
    x+=1;
}

for(var i = 0; i < 5; i+=1) {
    print format("for: i = ", i);
}

var z = 0;
while(true) {
    if(x+=1 == 5) break;
    print format("while (break): i = ", i);
}