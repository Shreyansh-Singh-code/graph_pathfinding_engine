#include "../include/export.hpp"

#include <fstream>
#include <iomanip>

void exportVisitedNodes(
    const Graph& g,
    const SearchResult& result,
    const std::string& filename
)
{
    std::ofstream out(filename);

    out << "order,lat,lon\n";

    for(size_t i=0;i<result.visitedNodes.size();i++)
    {
        int node = result.visitedNodes[i];

        out
        << i << ","
        << g.nodes[node].lat << ","
        << g.nodes[node].lon
        << "\n";
    }

    out.close();
}

void exportRoute(
    const Graph& g,
    const SearchResult& result,
    const std::string& filename
)
{
    std::ofstream out(filename);

    out << "step,node_id,lat,lon,cumulative_distance\n";

    double cumulative = 0.0;

    out << std::fixed << std::setprecision(8);

    for(size_t i = 0; i < result.path.size(); i++)
    {
        int node = result.path[i];

        if(i > 0)
        {
            int prev = result.path[i-1];

            for(const auto& edge : g.adj[prev])
            {
                if(edge.to == node)
                {
                    cumulative += edge.weight;
                    break;
                }
            }
        }

        out
            << i << ","
            << g.nodes[node].osm_id << ","
            << g.nodes[node].lat << ","
            << g.nodes[node].lon << ","
            << cumulative
            << "\n";
    }

    out.close();
}