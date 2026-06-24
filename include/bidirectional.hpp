#pragma once

#include "graph.hpp"
#include "dijkstra.hpp"

SearchResult bidirectionalDijkstra(
    const Graph& g,
    int source,
    int target
);