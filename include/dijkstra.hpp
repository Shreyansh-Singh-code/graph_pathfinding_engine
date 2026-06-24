#pragma once

#include "graph.hpp"
#include <vector>

struct SearchResult
{
    double distance;
    int nodesExpanded;

    std::vector<int> path;

    std::vector<int> visitedNodes;
};

SearchResult dijkstra(
    const Graph& g,
    int source,
    int target
);