# Neural-Network

## Description

Feed-forward neural network (FNN)

- Mesh type: Fully connected (Between layers)
- Activation function: tanh (Non-linear)
- Training method: Backpropagation

## Requirements
- CMake (Version >= 3.5)
- C++-Compiler (Standard >= C++17)

## Build

- "Data-Generator": cmake -H"tools/Data-Generator" -B"build/Data-Generator"
- "Neural-Network": cmake -H"." -B"build/Neural-Network"

## Run

- "Data-Generator": {app} \> {datafile}
- "Neural-Network": {app} {topology} {datafile} \> {resultfile}

### Example
- $ ./Data-Generator \> data.txt
- $ ./Neural-Network "2 2 1" data.txt \> results.txt
