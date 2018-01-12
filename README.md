# function-plotter
It plots any function you want into the console. The only obstacle is that<br>
if you use a function with different parameters, it will be required to add
that function template to the plot header file.

## Functions
### Constructor
Being its parameters the size and step
```c++
Graph graph(15, 1.0/20);
```

### Graph:fillValues()
```c++
double function1(double x) {
    return x*x*x;
}
...
graph.fillValues(&function1);
```

### Graph:plot()
```c++
graph.fillValues(&function1);
graph.plot();
```

### Graph:clearMemory()
Clears out the memory allocated for the plot values
```c++
graph.clearMemory();
```

### Graph:loop()
```c++
double function2(double x, double t) {
    return 0.1*cos(8*3.1416*t - 4*3.1416*x);
}
...
graph.loop(&function2);
```
