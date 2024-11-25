<div align="center">
<h1>CFroppy</h1>
Interpreter for <b>Froppy</b> programming language
</div>


<div align="center"><h3>Dependencies</h3></div>
<b>Languages:</b> C++23 <br />
<b>Build systems:</b> CMake <br />

<div align="center"><h3>How to build</h3></div>
1. Create a build directory and navigate into it

```shell
mkdir build
cd build
```

2. Build a project with CMake
```shell
cmake ..
make
sudo make install
# if possible use -j4 with make 
```

<div align="center"><h3>How to use</h3></div>
1. <b>Run prompt.</b> Usage: <i>"cfp"</i>.  <br />
2. <b>Run file.</b> Usage: <i>"cfp [path-to-file]"</i>.

<div align="center">
<h1>The Froppy Programming Language</h1>
Multi-paradigm interpreted programming language
</div>

<div align="center"><h3>Weak typing</h3></div>
In Froppy variables are not bound to a specific data type.

```froppy
let x; // by default, it is initialized to nil
println(x); // >> "nil"

x = 52; // now it is a integer
println(x); // >> 52
```

<div align="center"><h3>Dynamic scoping</h3></div>
Froppy has closures.

```froppy
fn factory() {
    fn instance() {
        println("factory::instance");
    }
    return instance; // return inner function
}

let foo = factory();
foo(); // >> "factory::instance"
```

<div align="center"><h3>Object-oriented</h3></div>
Froppy is object-oriented programing language, so it has classes and inheritance.

```froppy
class base { 
    let x;
    fn setX(x_) { 
        x = x_; 
    }
    fn getX() { 
        return x; 
    }
}

class derived : base { // derived is inherited from base
    fn setX(x_) {  // override method
        x=x_*2;
    }
}

let d = derived();
d.setX(3); // use overrided setX method
printlb(d.getX()); // >> 6
```

<div align="center"><h3>Documentation</h3></div>
Read more about Froppy language in documentation.