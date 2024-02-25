cmake_minimum_required(VERSION 3.5)
project("Neural-Network" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} app/Main.cpp
    src/reader/Reader.cpp src/network/Network.cpp
    src/network/Layer.cpp src/network/Neuron.cpp
    src/network/Edge.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src)
