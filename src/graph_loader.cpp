#include "../include/graph_loader.hpp"

#include <fstream>
#include <sstream>

Graph loadGraph(
    const std::string& nodesFile,
    const std::string& edgesFile
)
{
    Graph g;

    std::ifstream nodes(nodesFile);

    std::string line;

    getline(nodes, line);

    while (getline(nodes, line))
    {
        std::stringstream ss(line);

        std::string token;

        Node node;

        getline(ss, token, ',');
        node.osm_id = stoll(token);

        getline(ss, token, ',');
        node.lat = stod(token);

        getline(ss, token, ',');
        node.lon = stod(token);

        g.addNode(node);
    }

    nodes.close();

    std::ifstream edges(edgesFile);

    getline(edges, line);

    while (getline(edges, line))
    {
        std::stringstream ss(line);

        std::string token;

        int u, v;
        double w;

        getline(ss, token, ',');
        u = stoi(token);

        getline(ss, token, ',');
        v = stoi(token);

        getline(ss, token, ',');
        w = stod(token);

        g.addEdge(u, v, w);
    }

    edges.close();

    return g;
}