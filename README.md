# Neural-Network

## Description

Feed-forward neural network (FNN)

- Mesh type: Fully connected (Between layers)
- Activation function: tanh (Non-linear)
- Training method: Backpropagation

## Requirements

- CMake (Version >= 3.20)
- C++-Compiler (Standard >= C++23)

## Build

- "Data-Generator": cmake -H"tools/Data-Generator" -B"build/Data-Generator"
- "Neural-Network": cmake -H"." -B"build/Neural-Network"

## Run

1. "Data-Generator": {app} {mode} {count} \> {datafile}
2. "Neural-Network": {app} --topo {topology} --file {filepath} \[--verbosity {level}\] \> {resultfile}

### XOR

```
$ ./Data-Generator xor 10000 > data.txt
$ ./Neural-Network --topo "2 2 1" --file data.txt > results.txt
```

### MUL

```
$ ./Data-Generator mul 10000 > data.txt
$ ./Neural-Network --topo "4 8 6 4" --file data.txt > results.txt
```

### DIV

```
$ ./Data-Generator div 10000 > data.txt
$ ./Neural-Network --topo "20 32 16 10" --file data.txt > results.txt
```

### Disclaimer

- Make sure the input/output nodes match the generated training data.
