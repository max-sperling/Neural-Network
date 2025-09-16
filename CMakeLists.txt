cmake_minimum_required(VERSION 3.20)

project("Neural-Network")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TBB REQUIRED)

add_subdirectory(tools/Data-Generator)

add_executable(${PROJECT_NAME} app/Main.cpp
    src/network/Network.cpp src/network/Layer.cpp src/network/Neuron.cpp
    src/network/Edge.cpp src/reader/Reader.cpp src/utils/Arguments.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb)
