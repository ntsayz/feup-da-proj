//
// Created by ntsayz on 09-03-2023.
//

#include <queue>
#include <unordered_set>
#include "Graph.h"





void Graph::addNode(int nodeId) {
    nodes.emplace(nodeId, Node(nodeId));
}
void Graph::addNode(Node &node) {
    nodes.emplace(node.getId(),node);
}
void Graph::addEdge(Edge &edge) {
    adjacency_list[edge.getSource()].push_back(edge);
    Edge reverseEdge = Edge(edge.getDestination(), edge.getSource(), edge.getDistance());
    adjacency_list[reverseEdge.getSource()].push_back(reverseEdge);
}
void Graph::fillNodesFromAdjList() {
    // Iterate over the adjacency list
    for (const auto& entry : adjacency_list) {
        // Check if the node ID is not already in the nodes unordered_map
        if (nodes.find(entry.first) == nodes.end()) {
            // Add the node ID and its corresponding Node object to the nodes unordered_map
            nodes[entry.first] = Node(entry.first);  // Assumes Node(int id) constructor initializes a Node
        }

        // Now iterate over edges for each node in adjacency_list
        for (const auto& edge : entry.second) {
            // Check if the destination node ID is not already in the nodes unordered_map
            if (nodes.find(edge.getDestination()) == nodes.end()) {
                // Add the destination node ID and its corresponding Node object to the nodes unordered_map
                nodes[edge.getDestination()] = Node(edge.getDestination());  // Assumes Node(int id) constructor initializes a Node
            }
        }
    }
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
    auto start = std::chrono::high_resolution_clock::now();
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

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    // Print the minimum path
    std::cout << "Minimum Path: ";
    for (const auto& node : minPath) {
        std::cout << node << " ";
    }
    std::cout << "\nMinimum Distance: " << minDistance << std::endl;
    int choice;
    std::cin >> choice;
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

void Graph::solve_tsp_2approximation() {
    auto start = std::chrono::high_resolution_clock::now();
    // Create MST
    auto mst = createMST();

    // Traversal of the MST
    std::vector<int> traversal;
    std::unordered_map<int, bool> visited;

    std::stack<int> stack;
    stack.push(0);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        if (!visited[node]) {
            visited[node] = true;
            traversal.push_back(node);
            for (const auto& edge : mst[node]) {
                stack.push(edge.getDestination());
            }
        }
    }

    // Add the starting node to make it a cycle
    traversal.push_back(0);

    double totalDistance = 0.0;
    for (size_t i = 0; i < traversal.size() - 1; ++i) {
        int node1 = traversal[i];
        int node2 = traversal[i + 1];
        totalDistance += getEdge(node1, node2).getDistance();
    }

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    Utility::safe_print("Approximate TSP path using 2-approximation based on triangular inequality (MST):");
    for (const auto& node : traversal) {
        std::cout << node << " -> ";
    }
    Utility::safe_print("Total distance: "+ std::to_string(totalDistance));
    int i ;
    std::cin >>i;
}

std::unordered_map<int, std::vector<Edge>> Graph::createMST() {
    std::unordered_map<int, std::vector<Edge>> mst;  // The MST represented as an adj list
    std::priority_queue<Edge, std::vector<Edge>,std::greater<>> minHeap;  // Min-heap for the edges
    std::unordered_set<int> visited;

    for (const auto& edge : adjacency_list[0]) {
        minHeap.push(edge);
    }
    visited.insert(0);

    while (!minHeap.empty()) {
        Edge edge = minHeap.top();
        minHeap.pop();

        int source = edge.getSource();
        int destination = edge.getDestination();

        if (visited.count(destination) == 0) {
            mst[source].push_back(edge);

            visited.insert(destination);

            for (const auto& nextEdge : adjacency_list[destination]) {
                minHeap.push(nextEdge);
            }
        }
    }

    return mst;
}






