#pragma once

#include <vector>

struct Edge
{
    int to;
    double weight;
};

struct Node
{
    long long osm_id;

    double lat;
    double lon;
};

class Graph
{
public:

    std::vector<Node> nodes;

    std::vector<std::vector<Edge>> adj;
    std::vector<std::vector<Edge>> revAdj;

    void addNode(const Node& node);

    void addEdge(
        int u,
        int v,
        double weight
    );

    int size() const;
};