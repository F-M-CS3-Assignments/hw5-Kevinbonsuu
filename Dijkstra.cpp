
#include "Dijkstra.h"
#include "BetterPriorityQueue.h"
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

// Dijkstra's algorithm to find the shortest path from start to end in a weighted graph
// Time Complexity: O((V + E) * log V), assuming duplicate entries handled by visited set
int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    if (!g->IsPresent(start) || !g->IsPresent(end)) {
        throw invalid_argument("Start or end node does not exist in the graph.");
    }

    BetterPriorityQueue pq;
    std::unordered_map<nodekey_t, int> distance;
    std::unordered_set<nodekey_t> visited;

    distance[start] = 0;
    pq.push(BPQNode{0, false, start});

    while (!pq.empty()) {
        BPQNode current = pq.top();
        pq.pop();

        if (visited.count(current.gnode)) continue;
        visited.insert(current.gnode);

        if (current.gnode == end) {
            return current.pri;
        }

        for (const GraphEdge* edge : g->GetOutwardEdgesFrom(current.gnode)) {
            int newDist = current.pri + edge->weight;
            if (!distance.count(edge->to) || newDist < distance[edge->to]) {
                distance[edge->to] = newDist;
                pq.push(BPQNode{newDist, false, edge->to}); // don't use Update
            }
        }
    }

    return -1; // No path found
}
