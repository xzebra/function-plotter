# function-plotter

It plots any function you want into the console. Just type it into the console <br>
and it will do the work for you!

## Functions

### Constructor

Being its parameters the size and step:

```c++
Graph graph(10, 10);

![alt text](https://i.imgur.com/uyu9uD4.png)
```

### Graph:Plot(std::string expression)

```c++
Graph.Plot("0.1 * x");
```

![alt text](https://i.imgur.com/r4dxzzh.png)

### Graph:Loop(std::string expression)

```c++
graph.Loop("0.1*cos(8*3.1416*t - 4*3.1416*x)")
```

![alt text](https://i.imgur.com/pIkX6Ml.gif)
