


#include "Graph.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Internal adjacency list and nodes vector
//vector<nodekey_t> nodes;
//vector<vector<GraphEdge*>> adjList;

// Utility function to find if a specific edge already exists in the graph
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *>> adjList)
{
	if(adjList.size() == 0) return nullptr;

	for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++) {
		vector<GraphEdge*> row = adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++) {
			GraphEdge *cur = row.at(i);
			if(cur->from == gnFrom && cur->to == gnTo) {
				return cur;
			}
		}
	} 
	return nullptr;
}

// Utility function to convert an edge to string
string GraphEdgeToString(const GraphEdge* e) {
	return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}

// Adds a new node to the graph
void Graph::AddNode(nodekey_t key) {
	if(this->IsPresent(key)) {
		throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
	}
	nodes.push_back(key);
	adjList.push_back(vector<GraphEdge*>());
}

// Adds a directed edge between two nodes with a given weight
const GraphEdge *Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo, unsigned int w) {
	if(!this->IsPresent(gnFrom)) throw invalid_argument("No such node: " + to_string(gnFrom));
	if(!this->IsPresent(gnTo)) throw invalid_argument("No such node: " + to_string(gnTo));

	const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, adjList);
	if(dup != nullptr) {
		throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
	}

	GraphEdge *ge = new GraphEdge{gnFrom, gnTo, w};
	
	size_t idx = find(nodes.begin(), nodes.end(), gnFrom) - nodes.begin();
	adjList.at(idx).push_back(ge);
	
	return ge;
}

// Checks if a node is present in the graph
bool Graph::IsPresent(nodekey_t key) const {
	return find(nodes.begin(), nodes.end(), key) != nodes.end();
}

// Returns the set of edges going outward from a node
set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const {
	size_t idx = 0;
	while(idx < nodes.size() && nodes.at(idx) != node) idx++;
	if(idx == nodes.size()) throw invalid_argument("No such node: " + to_string(node));

	set<const GraphEdge*> result;
	for(GraphEdge* e : adjList.at(idx)) {
		if(e->from == node) result.insert(e);
	}
	return result;
}

// Returns all node keys
set<nodekey_t> Graph::GetNodes() const {
	set<nodekey_t> result;
	for(nodekey_t n : nodes) result.insert(n);
	return result;
}

// Returns the number of nodes
size_t Graph::Order() const {
	return nodes.size();
}

// Returns the number of edges
size_t Graph::Size() const {
	size_t total = 0;
	for(const auto& row : adjList) {
		total += row.size();
	}
	return total;
}

// Converts all nodes to a printable string
string Graph::NodesToString() const {
	if(nodes.empty()) return "[]";
	string str = "[";
	for(size_t i = 0; i < nodes.size(); i++) {
		str += "(" + to_string(nodes[i]) + ")";
		if(i < nodes.size() - 1) str += ", ";
	}
	str += "]";
	return str;
}

// Converts all edges to a printable string
string Graph::EdgesToString() const {
	if(adjList.empty()) return "[]";
	string str = "[";
	size_t count = 0;
	size_t total = Size();
	for(const auto& row : adjList) {
		for(GraphEdge* cur : row) {
			str += GraphEdgeToString(cur);
			if(++count < total) str += ", ";
		}
	}
	str += "]";
	return str;
}

// Destructor to release memory and prevent leaks
Graph::~Graph() {
	for(auto& row : adjList) {
		for(GraphEdge* edge : row) {
			delete edge;
		}
		row.clear();
	}
	nodes.clear();
	adjList.clear();
}


