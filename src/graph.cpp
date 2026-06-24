#include "../include/graph.hpp"

void Graph::addNode(const Node& node)
{
    nodes.push_back(node);

    adj.emplace_back();

    revAdj.emplace_back();
}

void Graph::addEdge(
    int u,
    int v,
    double weight
)
{
    adj[u].push_back({
        v,
        weight
    });

    revAdj[v].push_back({
        u,
        weight
    });
}

int Graph::size() const
{
    return nodes.size();
}