#pragma once

#include "graph.hpp"
#include "dijkstra.hpp"

#include <string>

void exportRoute(
    const Graph& g,
    const SearchResult& result,
    const std::string& filename
);

void exportVisitedNodes(
    const Graph& g,
    const SearchResult& result,
    const std::string& filename
);