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


bool Graph::hasEdge(int source, int destination)  {
    const std::vector<Edge>& edges = adjacency_list.at(source);
    for (const Edge& edge : edges) {
        if (edge.getDestination() == destination) {
            return true;
        }
    }
    return false;
}


void Graph::tsp_backtracking(int curr_pos, std::vector<bool>& visited, int n, int count, double cost, std::vector<int>& path, double& min_cost) {
    if (count == n && hasEdge(curr_pos, 0)) {
        path.push_back(0);
        min_cost = std::min(min_cost, cost + getEdgeWeight(curr_pos, 0));
        path.pop_back();
        return;
    }

    for (const auto& edge : getEdgesFromNode(curr_pos)) {
        int next_node = edge.getDestination();
        if (!visited[next_node]) {
            visited[next_node] = true;
            path.push_back(next_node);

            tsp_backtracking(next_node, visited, n, count + 1, cost + edge.getDistance(), path, min_cost);

            path.pop_back();
            visited[next_node] = false;
        }
    }
}

void Graph::solve_tsp_backtracking() {
    int n = getNumNodes();

    std::vector<bool> visited(n, false);
    visited[0] = true;

    std::vector<int> path;
    path.push_back(0);

    double min_cost = std::numeric_limits<double>::max();

    tsp_backtracking( 0, visited, n, 1, 0.0, path, min_cost);

    std::cout << "Optimal Tour: ";
    for (int node : path) {
        std::cout << node << " -> ";
    }
    std::cout << "0" << std::endl;

    std::cout << "Optimal Cost: " << min_cost << std::endl;
}

int Graph::getNumNodes()  {
    return nodes.size();
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

