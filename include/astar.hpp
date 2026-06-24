#pragma once

#include "graph.hpp"
#include "dijkstra.hpp"

SearchResult astar(
    const Graph& g,
    int source,
    int target
);