cmake_minimum_required(VERSION 3.15)

project(GraphPathfindingEngine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

add_executable(pathfinder
    src/main.cpp
    src/graph.cpp
    src/graph_loader.cpp
    src/haversine.cpp
    src/dijkstra.cpp
    src/astar.cpp
    src/bidirectional.cpp
    src/weighted_astar.cpp
    src/export.cpp
)

add_executable(benchmark
    benchmark/benchmark.cpp
    src/graph.cpp
    src/graph_loader.cpp
    src/haversine.cpp
    src/dijkstra.cpp
    src/astar.cpp
    src/bidirectional.cpp
    src/weighted_astar.cpp
    src/export.cpp
)