#pragma once

#include "graph.hpp"
#include "dijkstra.hpp"

SearchResult weightedAStar(
    const Graph& g,
    int source,
    int target,
    double epsilon
);