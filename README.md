# Neural-Network

## Description

Feed-forward neural network (FNN)

- Mesh type: Fully connected (Between layers)
- Activation function: tanh (Non-linear)
- Training method: Backpropagation

## Requirements

- CMake (Version >= 3.20)
- C++-Compiler (Standard >= C++23)
- oneTBB

## Build

- "Data-Generator": cmake -H"tools/Data-Generator" -B"build/Data-Generator"
- "Neural-Network": cmake -H"." -B"build/Neural-Network"

## Run

1. "Data-Generator": {app} {mode} \> {datafile}
2. "Neural-Network": {app} {topology} {datafile} \> {resultfile}

### XOR

```
$ ./Data-Generator "xor" > data.txt
$ ./Neural-Network "2 2 1" data.txt > results.txt
```

### MUL

```
$ ./Data-Generator "mul" > data.txt
$ ./Neural-Network "4 8 6 4" data.txt > results.txt
```

### DIV

```
$ ./Data-Generator "div" > data.txt
$ ./Neural-Network "20 32 16 10" data.txt > results.txt
```

### Disclaimer

- Make sure the input/output nodes match the generated training data.
