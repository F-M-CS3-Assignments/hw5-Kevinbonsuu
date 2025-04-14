
#include "BetterPriorityQueue.h"
#include <sstream>
#include <algorithm>

using namespace std;

// Check if a node is present in the queue
bool BetterPriorityQueue::Contains(const BPQNode& target) const {
    for (const BPQNode& n : this->c) {
        if (n == target) return true;
    }
    return false;
}

// Update a node's priority if it's lower, preserving heap order
bool BetterPriorityQueue::Update(const BPQNode& updated) {
    bool updatedFlag = false;
    for (BPQNode& n : this->c) {
        if (n.gnode == updated.gnode) {
            if (updated.pri < n.pri) {
                n.pri = updated.pri;
                updatedFlag = true;
            }
            break;
        }
    }

    if (updatedFlag) {
        make_heap(this->c.begin(), this->c.end(), this->comp);
    }
    return updatedFlag;
}

// Return string representation of the whole queue (sorted for predictable output)
string BetterPriorityQueue::ToString() const {
    vector<BPQNode> temp = this->c;
    sort(temp.begin(), temp.end(), [](const BPQNode& a, const BPQNode& b) {
        if (a.pri == b.pri) return a.gnode < b.gnode;
        return a.pri < b.pri;
    });

    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < temp.size(); ++i) {
        ss << BPQNodeToString(temp[i]);
        if (i != temp.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

// Convert a BPQNode to string format
string BetterPriorityQueue::BPQNodeToString(const BPQNode& n) {
    return "(" + to_string(n.gnode) + ", pri: " + to_string(n.pri) + ")";
}