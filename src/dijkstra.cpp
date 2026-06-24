#include "../include/dijkstra.hpp"

#include <queue>
#include <limits>
#include <algorithm>

SearchResult dijkstra(
    const Graph& g,
    int source,
    int target
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

    pq.push({0.0, source});

    int expanded = 0;

    while(!pq.empty())
    {
        auto [currentDist, u] =
            pq.top();

        pq.pop();

        if(currentDist > dist[u])
            continue;

        expanded++;
        visited.push_back(u);

        if(u == target)
            break;

        for(const auto& edge :
            g.adj[u])
        {
            int v = edge.to;

            double nd =
                dist[u] +
                edge.weight;

            if(nd < dist[v])
            {
                dist[v] = nd;

                parent[v] = u;

                pq.push({nd, v});
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