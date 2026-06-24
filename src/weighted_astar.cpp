#include "../include/weighted_astar.hpp"
#include "../include/haversine.hpp"

#include <queue>
#include <limits>
#include <algorithm>

static double heuristic(
    const Graph& g,
    int current,
    int target
)
{
    const auto& a = g.nodes[current];
    const auto& b = g.nodes[target];

    return haversine(
        a.lat,
        a.lon,
        b.lat,
        b.lon
    );
}

SearchResult weightedAStar(
    const Graph& g,
    int source,
    int target,
    double epsilon
)
{
    const double INF =
        std::numeric_limits<double>::infinity();

    int n = g.size();

    std::vector<double> dist(n, INF);
    std::vector<int> parent(n, -1);
    std::vector<int> visited;

    using State =
        std::pair<double,int>;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pq;

    dist[source] = 0.0;

    pq.push({
        epsilon *
        heuristic(
            g,
            source,
            target
        ),
        source
    });

    int expanded = 0;

    while(!pq.empty())
    {
        auto [fscore, u] =
            pq.top();

        pq.pop();

        double expected =
            dist[u] +
            epsilon *
            heuristic(
                g,
                u,
                target
            );

        if(fscore > expected)
            continue;

        expanded++;
        visited.push_back(u);
        if(u == target)
            break;

        for(const auto& edge :
            g.adj[u])
        {
            int v = edge.to;

            double newDist =
                dist[u] +
                edge.weight;

            if(newDist < dist[v])
            {
                dist[v] = newDist;

                parent[v] = u;

                double priority =
                    newDist +
                    epsilon *
                    heuristic(
                        g,
                        v,
                        target
                    );

                pq.push({
                    priority,
                    v
                });
            }
        }
    }

    std::vector<int> path;

    if(dist[target] != INF)
    {
        for(
            int cur = target;
            cur != -1;
            cur = parent[cur]
        )
        {
            path.push_back(cur);
        }

        std::reverse(
            path.begin(),
            path.end()
        );
    }

    return {
        dist[target],
        expanded,
        path,
        visited
    };
}