#include "../include/graph_loader.hpp"
#include "../include/dijkstra.hpp"
#include "../include/astar.hpp"
#include "../include/bidirectional.hpp"
#include "../include/weighted_astar.hpp"

#include "../benchmark/benchmark_utils.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>

void printStats(
    const std::string& name,
    const AlgoStats& stats
)
{
    std::cout
        << "\n=====================\n";

    std::cout
        << name
        << "\n";

    std::cout
        << "Queries: "
        << stats.successfulQueries
        << "\n";

    std::cout
        << "Average Time (ms): "
        << stats.totalTime /
           stats.successfulQueries
        << "\n";

    std::cout
        << "Average Expanded: "
        << (double)
           stats.totalExpanded /
           stats.successfulQueries
        << "\n";

    std::cout
        << "Average Distance: "
        << stats.totalDistance /
           stats.successfulQueries
        << "\n";
}

int main()
{
    Graph g = loadGraph(
        "../data/processed/nodes.csv",
        "../data/processed/edges.csv"
    );

    std::cout
        << "Graph Loaded\n";

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

    const int NUM_QUERIES = 100;

    std::mt19937 rng(42);

    std::uniform_int_distribution<int>
        nodeDist(
            0,
            g.size() - 1
        );

    AlgoStats dijkstraStats;
    AlgoStats astarStats;
    AlgoStats bidiStats;

    AlgoStats wa12Stats;
    AlgoStats wa15Stats;
    AlgoStats wa20Stats;

    std::ofstream csv(
        "../results/benchmark_results.csv"
    );

    csv
    << "Algorithm,Query,TimeMs,Expanded,Distance\n";

    for(int i = 0; i < NUM_QUERIES; i++)
    {
        int source =
            nodeDist(rng);

        int target =
            nodeDist(rng);

        if(source == target)
        {
            i--;
            continue;
        }

        //--------------------------------
        // DIJKSTRA
        //--------------------------------

        auto start =
            std::chrono::high_resolution_clock::now();

        auto dres =
            dijkstra(
                g,
                source,
                target
            );

        auto end =
            std::chrono::high_resolution_clock::now();

        double dTime =
            std::chrono::duration<double,std::milli>(
                end - start
            ).count();

        if(dres.path.empty())
        {
            i--;
            continue;
        }

        dijkstraStats.totalTime += dTime;
        dijkstraStats.totalExpanded += dres.nodesExpanded;
        dijkstraStats.totalDistance += dres.distance;
        dijkstraStats.successfulQueries++;

        csv
        << "Dijkstra,"
        << i << ","
        << dTime << ","
        << dres.nodesExpanded << ","
        << dres.distance
        << "\n";

        //--------------------------------
        // ASTAR
        //--------------------------------

        start =
            std::chrono::high_resolution_clock::now();

        auto ares =
            astar(
                g,
                source,
                target
            );

        end =
            std::chrono::high_resolution_clock::now();

        double aTime =
            std::chrono::duration<double,std::milli>(
                end - start
            ).count();

        astarStats.totalTime += aTime;
        astarStats.totalExpanded += ares.nodesExpanded;
        astarStats.totalDistance += ares.distance;
        astarStats.successfulQueries++;

        csv
        << "AStar,"
        << i << ","
        << aTime << ","
        << ares.nodesExpanded << ","
        << ares.distance
        << "\n";

        //--------------------------------
        // BIDIRECTIONAL
        //--------------------------------

        start =
            std::chrono::high_resolution_clock::now();

        auto bres =
            bidirectionalDijkstra(
                g,
                source,
                target
            );

        end =
            std::chrono::high_resolution_clock::now();

        double bTime =
            std::chrono::duration<double,std::milli>(
                end - start
            ).count();

        bidiStats.totalTime += bTime;
        bidiStats.totalExpanded += bres.nodesExpanded;
        bidiStats.totalDistance += bres.distance;
        bidiStats.successfulQueries++;

        csv
        << "Bidirectional,"
        << i << ","
        << bTime << ","
        << bres.nodesExpanded << ","
        << bres.distance
        << "\n";

        //--------------------------------
        // WEIGHTED A*
        //--------------------------------

        auto runWeighted =
        [&](double eps,
            AlgoStats& stats,
            const std::string& name)
        {
            auto ws =
                std::chrono::high_resolution_clock::now();

            auto wres =
                weightedAStar(
                    g,
                    source,
                    target,
                    eps
                );

            auto we =
                std::chrono::high_resolution_clock::now();

            double wTime =
                std::chrono::duration<double,std::milli>(
                    we - ws
                ).count();

            stats.totalTime += wTime;
            stats.totalExpanded += wres.nodesExpanded;
            stats.totalDistance += wres.distance;
            stats.successfulQueries++;

            csv
            << name << ","
            << i << ","
            << wTime << ","
            << wres.nodesExpanded << ","
            << wres.distance
            << "\n";
        };

        runWeighted(
            1.2,
            wa12Stats,
            "WAStar1.2"
        );

        runWeighted(
            1.5,
            wa15Stats,
            "WAStar1.5"
        );

        runWeighted(
            2.0,
            wa20Stats,
            "WAStar2.0"
        );

        if((i + 1) % 10 == 0)
        {
            std::cout
                << "Completed "
                << (i + 1)
                << "/"
                << NUM_QUERIES
                << "\n";
        }
    }

    csv.close();

    printStats(
        "DIJKSTRA",
        dijkstraStats
    );

    printStats(
        "A STAR",
        astarStats
    );

    printStats(
        "BIDIRECTIONAL",
        bidiStats
    );

    printStats(
        "WA*(1.2)",
        wa12Stats
    );

    printStats(
        "WA*(1.5)",
        wa15Stats
    );

    printStats(
        "WA*(2.0)",
        wa20Stats
    );

    return 0;
}