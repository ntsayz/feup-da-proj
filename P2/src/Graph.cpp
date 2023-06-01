//
// Created by ntsayz on 09-03-2023.
//

#include "Graph.h"


void Graph::addNode(int nodeId) {
    nodes.emplace(nodeId, Node(nodeId));
}
void Graph::addNode(Node &node) {
    nodes.emplace(node.getId(),node);
}
void Graph::addEdge(Edge &edge) {
    adjacency_list[edge.getSource()].push_back(edge);
}

bool Graph::hasEdge(int source, int destination) {
    if (adjacency_list.find(source) != adjacency_list.end()) {
        for (const auto& edge : adjacency_list[source]) {
            if (edge.getDestination() == destination) {
                return true;
            }
        }
    }
    return false;
}

Edge Graph::getEdge(int source, int destination) {
    if (hasEdge(source, destination)) {
        for (const auto& edge : adjacency_list.at(source)) {
            if (edge.getDestination() == destination) {
                return edge;
            }
        }
    }
    // If the edge is not found, return a default-constructed Edge
    return Edge();
}

double Graph::getEdgeWeight(int source, int destination) {
    const std::vector<Edge>& edges = adjacency_list.at(source);
    for (const Edge& edge : edges) {
        if (edge.getDestination() == destination) {
            return edge.getDistance();
        }
    }
    return 0.0;
}

std::vector<Edge> Graph::getEdgesFromNode(int nodeId) const {
    return adjacency_list.at(nodeId);
}

void Graph::reset() {
    adjacency_list.clear();
    nodes.clear();
    std::printf("adj list %zu nodes %zu\n",adjacency_list.size(),nodes.size());
}

void Graph::solve_tsp_backtracking() {
    // Initialize variables
    std::vector<int> visited;
    double minDistance = std::numeric_limits<double>::max();
    double currentDistance = 0.0;
    std::vector<int> currentPath;
    std::vector<int> minPath;

    // Start the backtracking algorithm from node 0
    int startingNode = 0;
    visited.push_back(startingNode);
    currentPath.push_back(startingNode);

    // Call the backtracking helper function
    solve_tsp_backtracking_helper(visited, minDistance, currentDistance, startingNode, currentPath, minPath);

    // Print the minimum path
    std::cout << "Minimum Path: ";
    for (const auto& node : minPath) {
        std::cout << node << " ";
    }
    std::cout << "\nMinimum Distance: " << minDistance << std::endl;
}


void Graph::solve_tsp_backtracking_helper(std::vector<int>& visited, double& minDistance, double currentDistance, int currentNode, std::vector<int>& currentPath, std::vector<int>& minPath) {
    // Base case: All nodes have been visited
    if (visited.size() == nodes.size()) {
        // Check if the current tour is better than the minimum tour distance found so far
        if (currentDistance + getEdge(currentNode, 0).getDistance() < minDistance) {
            minDistance = currentDistance + getEdge(currentNode, 0).getDistance();
            minPath = currentPath;
            minPath.push_back(0);  // Append the starting node to complete the path
        }
        return;
    }

    // Iterate over all unvisited nodes
    for (const auto& edge : adjacency_list[currentNode]) {
        int nextNode = edge.getDestination();

        // Check if the next node has been visited
        if (std::find(visited.begin(), visited.end(), nextNode) == visited.end()) {
            // Add the current node to the visited list and path
            visited.push_back(nextNode);
            currentPath.push_back(nextNode);

            // Update the current tour distance
            currentDistance += edge.getDistance();

            // Recursively call the backtracking function with the next node
            solve_tsp_backtracking_helper(visited, minDistance, currentDistance, nextNode, currentPath, minPath);

            // Remove the current node from the visited list, path, and update the current tour distance
            visited.pop_back();
            currentPath.pop_back();
            currentDistance -= edge.getDistance();
        }
    }
}

