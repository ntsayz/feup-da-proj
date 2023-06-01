//
// Created by ntsayz on 09-03-2023.
//

#include "Graph.h"


void Graph::addNode(int nodeId) {
    nodes.emplace(nodeId, Node(nodeId));
}
void Graph::addNode(const Node &node) {
    nodes.emplace(node.getId(),node);
}
void Graph::addEdge(const Edge &edge) {
    adjacency_list[edge.getSource()].push_back(edge);
}

void Graph::reset() {
    adjacency_list.clear();
    nodes.clear();
}

