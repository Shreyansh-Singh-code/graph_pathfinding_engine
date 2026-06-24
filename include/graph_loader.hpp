#pragma once

#include "graph.hpp"
#include <string>

Graph loadGraph(
    const std::string& nodesFile,
    const std::string& edgesFile
);