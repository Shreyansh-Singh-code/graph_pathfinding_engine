# Graph Pathfinding Engine
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/Build-CMake-green)
![OpenStreetMap](https://img.shields.io/badge/Dataset-OpenStreetMap-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)


A high-performance graph routing engine built in **C++17** for computing shortest paths on real-world road networks. The project implements and benchmarks multiple shortest-path algorithms on a **Delhi OpenStreetMap (OSM)** road graph containing over **183,000 nodes** and **499,000 directed edges**, along with visualization tools for route rendering and algorithm comparison.

---

## Features

* Built a graph representation from real OpenStreetMap road network data.
* Implemented multiple shortest-path algorithms:

  * Dijkstra's Algorithm
  * A* Search
  * Bidirectional Dijkstra
  * Weighted A* Search
* Haversine-based heuristic for geospatial routing.
* Automated benchmark framework for performance evaluation.
* Interactive route visualization using Folium.
* Search frontier export for algorithm visualization.
* Benchmark result generation and plotting with Python.

---

## Dataset

The project uses a processed OpenStreetMap road network of Delhi.

| Metric               |                        Value |
| -------------------- | ---------------------------: |
| Nodes                |                      183,747 |
| Directed Edges       |                      499,345 |
| Graph Representation |               Adjacency List |
| Edge Weight          | Geographic Distance (meters) |


The repository does not include the processed OpenStreetMap dataset because of GitHub file size limits.

Generate the dataset using:

```bash
python scripts/download_delhi.py
python scripts/export_graph.py
```

This will create:

```
data/raw/delhi.graphml
data/processed/nodes.csv
data/processed/edges.csv
```

---

## Algorithms Implemented

### Dijkstra

* Guarantees optimal shortest path.
* Explores the graph uniformly.
* Baseline algorithm for comparison.

### A*

* Uses Haversine distance as an admissible heuristic.
* Significantly reduces explored nodes while preserving optimality.

### Bidirectional Dijkstra

* Simultaneously searches from source and destination.
* Reduces search space by meeting in the middle.

### Weighted A*

Uses

[
f(n)=g(n)+\epsilon h(n)
]

where **ε > 1** trades optimality for speed.

Implemented values:

* ε = 1.2
* ε = 1.5
* ε = 2.0

---

# Benchmark Results

Benchmarks were performed over **100 randomly generated routing queries**.

| Algorithm              | Avg Time (ms) | Avg Expanded Nodes | Avg Distance (m) |
| ---------------------- | ------------: | -----------------: | ---------------: |
| Dijkstra               |         14.70 |             91,548 |           21,507 |
| Bidirectional Dijkstra |          9.82 |             56,844 |           21,507 |
| A*                     |          5.11 |             24,157 |           21,507 |
| Weighted A* (ε = 1.2)  |      **2.87** |         **10,586** |           21,729 |
| Weighted A* (ε = 1.5)  |          2.17 |             11,445 |           22,921 |
| Weighted A* (ε = 2.0)  |      **1.22** |          **5,750** |           23,823 |

---

## Performance Highlights

* **A*** reduced explored nodes by **73.6%** compared to Dijkstra while preserving optimal shortest paths.
* **Weighted A* (ε = 1.2)** achieved approximately **5.1× speedup** over Dijkstra with only **1.03% path inflation**.
* **Weighted A* (ε = 2.0)** achieved approximately **12× speedup**, demonstrating the trade-off between execution time and solution optimality.

---

## Project Structure

```
graph-pathfinding-engine/

├── include/
│   ├── graph.hpp
│   ├── graph_loader.hpp
│   ├── dijkstra.hpp
│   ├── astar.hpp
│   ├── bidirectional.hpp
│   ├── weighted_astar.hpp
│   ├── export.hpp
│   └── haversine.hpp
│
├── src/
│   ├── graph.cpp
│   ├── graph_loader.cpp
│   ├── dijkstra.cpp
│   ├── astar.cpp
│   ├── bidirectional.cpp
│   ├── weighted_astar.cpp
│   ├── export.cpp
│   ├── haversine.cpp
│   └── main.cpp
│
├── benchmarks/
│   ├── benchmark.cpp
│   └── benchmark_utils.hpp
│
├── scripts/
│   ├── benchmark.py
│   ├── comparison.py
│   └── visualize_route.py
│
├── data/
│
├── results/
│
└── CMakeLists.txt
```

---

## Building

```bash
mkdir build
cd build

cmake -G "MinGW Makefiles" ..

mingw32-make
```

---

## Running

### Generate Route

```bash
./pathfinder
```

This exports:

* route CSVs
* frontier CSVs

to the `results/` directory.

---

### Benchmark Algorithms

```bash
./benchmark
```

Outputs:

* Benchmark statistics
* `benchmark_results.csv`

---

### Generate Benchmark Plots

```bash
cd scripts

python benchmark.py
```

Generates:

* runtime comparison
* expanded node comparison
* speedup comparison
* path inflation comparison

---

### Visualize Routes

```bash
python comparison.py
```

Generates:

```
results/comparison.html
```

which provides an interactive visualization of all implemented algorithms and their search frontiers.

---

## Technologies Used

* C++17
* CMake
* STL
* Python
* Pandas
* Matplotlib
* Folium
* OpenStreetMap

---

## Future Work

* Search frontier animation
* Interactive algorithm selector
* ALT (A* with Landmarks)
* Contraction Hierarchies
* Dynamic traffic-aware routing
* Turn penalty modelling
* Parallel shortest-path search

---

## License

This project is released under the MIT License.
