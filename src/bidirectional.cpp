#include "../include/bidirectional.hpp"

#include <queue>
#include <limits>
#include <algorithm>

SearchResult bidirectionalDijkstra(
    const Graph& g,
    int source,
    int target
)
{
    const double INF =
        std::numeric_limits<double>::infinity();

    int n = g.size();

    std::vector<double> distF(n, INF);
    std::vector<double> distB(n, INF);
    std::vector<int> visited;
    std::vector<int> parentF(n, -1);
    std::vector<int> parentB(n, -1);

    using State =
        std::pair<double,int>;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pqF;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pqB;

    distF[source] = 0.0;
    distB[target] = 0.0;

    pqF.push({0.0, source});
    pqB.push({0.0, target});

    double bestDistance = INF;
    int meetingNode = -1;

    int expanded = 0;

    while(
        !pqF.empty() &&
        !pqB.empty()
    )
    {
        //--------------------------------
        // FORWARD STEP
        //--------------------------------

        auto [dF, u] = pqF.top();
        pqF.pop();

        if(dF > distF[u])
            continue;

        expanded++;
        visited.push_back(u);
        if(distB[u] != INF)
        {
            double candidate =
                distF[u] + distB[u];

            if(candidate < bestDistance)
            {
                bestDistance = candidate;
                meetingNode = u;
            }
        }

        for(const auto& edge : g.adj[u])
        {
            int v = edge.to;

            double nd =
                distF[u] +
                edge.weight;

            if(nd < distF[v])
            {
                distF[v] = nd;

                parentF[v] = u;

                pqF.push({
                    nd,
                    v
                });
            }
        }

        //--------------------------------
        // BACKWARD STEP
        //--------------------------------

        auto [dB, x] = pqB.top();
        pqB.pop();

        if(dB > distB[x])
            continue;

        expanded++;

        if(distF[x] != INF)
        {
            double candidate =
                distF[x] + distB[x];

            if(candidate < bestDistance)
            {
                bestDistance = candidate;
                meetingNode = x;
            }
        }

        for(const auto& edge :
            g.revAdj[x])
        {
            int v = edge.to;

            double nd =
                distB[x] +
                edge.weight;

            if(nd < distB[v])
            {
                distB[v] = nd;

                parentB[v] = x;

                pqB.push({
                    nd,
                    v
                });
            }
        }

        //--------------------------------
        // EARLY STOPPING
        //--------------------------------

        if(
            !pqF.empty() &&
            !pqB.empty()
        )
        {
            if(
                pqF.top().first +
                pqB.top().first
                >=
                bestDistance
            )
            {
                break;
            }
        }
    }

    //--------------------------------
    // NO PATH
    //--------------------------------

    if(meetingNode == -1)
    {
        return {
            INF,
            expanded,
            {}
        };
    }

    //--------------------------------
    // RECONSTRUCT PATH
    //--------------------------------

    std::vector<int> left;

    for(
        int cur = meetingNode;
        cur != -1;
        cur = parentF[cur]
    )
    {
        left.push_back(cur);
    }

    std::reverse(
        left.begin(),
        left.end()
    );

    std::vector<int> right;

    int cur = parentB[meetingNode];

    while(cur != -1)
    {
        right.push_back(cur);
        cur = parentB[cur];
    }

    left.insert(
        left.end(),
        right.begin(),
        right.end()
    );

    return {
        bestDistance,
        expanded,
        left, 
        visited
    };
}