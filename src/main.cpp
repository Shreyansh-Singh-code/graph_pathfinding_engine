#include "../include/graph_loader.hpp"
#include "../include/dijkstra.hpp"
#include "../include/astar.hpp"
#include "../include/bidirectional.hpp"
#include "../include/weighted_astar.hpp"
#include "../include/export.hpp"

#include <iostream>

int main()
{
    //----------------------------------------
    // Load Graph
    //----------------------------------------

    Graph g = loadGraph(
        "../data/processed/nodes.csv",
        "../data/processed/edges.csv"
    );

    std::cout << "Graph Loaded\n";

    std::cout
        << "Nodes: "
        << g.nodes.size()
        << "\n";

    long long edgeCount = 0;

    for(const auto& nbrs : g.adj)
        edgeCount += nbrs.size();

    std::cout
        << "Edges: "
        << edgeCount
        << "\n\n";

    //----------------------------------------
    // Choose Route
    //----------------------------------------

    int source = 0;
    int target = 1000;

    //----------------------------------------
    // Run Algorithms
    //----------------------------------------

    auto dres =
        dijkstra(
            g,
            source,
            target
        );

    auto ares =
        astar(
            g,
            source,
            target
        );

    auto bres =
        bidirectionalDijkstra(
            g,
            source,
            target
        );

    auto wres =
        weightedAStar(
            g,
            source,
            target,
            1.2
        );

    //----------------------------------------
    // Export Routes
    //----------------------------------------

    exportRoute(
        g,
        dres,
        "../results/dijkstra_route.csv"
    );

    exportRoute(
        g,
        ares,
        "../results/astar_route.csv"
    );

    exportRoute(
        g,
        bres,
        "../results/bidirectional_route.csv"
    );

    exportRoute(
        g,
        wres,
        "../results/weighted_route.csv"
    );

    //----------------------------------------
    // Export Search Frontiers
    //----------------------------------------

    exportVisitedNodes(
        g,
        dres,
        "../results/dijkstra_frontier.csv"
    );

    exportVisitedNodes(
        g,
        ares,
        "../results/astar_frontier.csv"
    );

    exportVisitedNodes(
        g,
        bres,
        "../results/bidirectional_frontier.csv"
    );

    exportVisitedNodes(
        g,
        wres,
        "../results/weighted_frontier.csv"
    );

    //----------------------------------------
    // Console Summary
    //----------------------------------------

    auto printResult =
    [](const std::string& name,
       const SearchResult& res)
    {
        std::cout
            << "----------------------------\n";

        std::cout
            << name
            << "\n";

        std::cout
            << "Distance : "
            << res.distance
            << " m\n";

        std::cout
            << "Expanded : "
            << res.nodesExpanded
            << "\n";

        std::cout
            << "Path Nodes : "
            << res.path.size()
            << "\n";

        std::cout
            << "Visited Nodes : "
            << res.visitedNodes.size()
            << "\n\n";
    };

    printResult(
        "Dijkstra",
        dres
    );

    printResult(
        "A*",
        ares
    );

    printResult(
        "Bidirectional",
        bres
    );

    printResult(
        "Weighted A* (ε = 1.2)",
        wres
    );

    std::cout
        << "====================================\n";

    std::cout
        << "Export Complete!\n\n";

    std::cout
        << "Generated Files:\n";

    std::cout
        << "dijkstra_route.csv\n"
        << "astar_route.csv\n"
        << "bidirectional_route.csv\n"
        << "weighted_route.csv\n\n";

    std::cout
        << "dijkstra_frontier.csv\n"
        << "astar_frontier.csv\n"
        << "bidirectional_frontier.csv\n"
        << "weighted_frontier.csv\n";

    return 0;
}