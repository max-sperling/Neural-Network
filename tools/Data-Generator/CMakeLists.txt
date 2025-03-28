cmake_minimum_required(VERSION 3.5)
project("Data-Generator" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
    src/Main.cpp)
