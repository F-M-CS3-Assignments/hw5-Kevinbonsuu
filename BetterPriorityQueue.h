#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <string>
#include "Graph.h" // for nodekey_t

// Struct for priority queue nodes
struct BPQNode {
    int pri = INT_MAX;
    bool visited = false;
    nodekey_t gnode = INVALID_NODE_KEY;

    bool operator<(const BPQNode &other) const { return pri < other.pri; }
    bool operator>(const BPQNode &other) const { return pri > other.pri; }
    bool operator==(const BPQNode &other) const { return this->gnode == other.gnode; }
};

// Priority queue with extra methods for Dijkstra
class BetterPriorityQueue : public std::priority_queue<BPQNode, std::vector<BPQNode>, std::greater<BPQNode>> {
public:
    bool Contains(const BPQNode& target) const;
    bool Update(const BPQNode& updated);
    std::string ToString() const;
    static std::string BPQNodeToString(const BPQNode& n);
};

#endif
