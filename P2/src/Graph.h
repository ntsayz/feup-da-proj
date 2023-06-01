//
// Created by ntsayz on 09-03-2023.
//

#include <vector>
#include <unordered_map>
#include "Edge.h"
#include "Node.h"

#ifndef SRC_GRAPH_H
#define SRC_GRAPH_H


class Graph {
public:
    /**
 * @brief Adds a node ID to the graph
 * @param nodeId The ID of the node to be added
 */
    void addNode(int nodeId);
    void addNode(const Node &nodeId);

    /**
     * @brief Adds an edge to the graph
     * @param edge The edge to be added
     */
    void addEdge(const Edge& edge);

    /**
     * @brief Returns a vector of all edges going out from a specified node
     * @param nodeId The ID of the node to get the edges for
     * @return A vector of all edges going out from the specified node
     */
    std::vector<Edge> getEdgesFromNode(int nodeId) const;

    /**
     * @brief Returns a vector of all edges going into a specified node
     * @param nodeId The ID of the node to get the edges for
     * @return A vector of all edges going into the specified node
     */
    std::vector<Edge> getEdgesToNode(int nodeId) const;

    /**
     * @brief Returns a node obj
     * @param id The id of the node to get
     * @return Node
     */
    Node getNodeObj(int id) const;

    void printGraph() const {
        for (const auto& node : adjacency_list) {
            std::cout << "Node " << node.first << " is connected to: \n";
            for (const auto& edge : node.second) {
                std::cout << "Node " << edge.getDestination() << " with a distance of " << edge.getDistance() << "\n";
            }
            std::cout << "------\n";
        }
    }


    void reset();

    void solve_tsp_backtracking();

private:
    bool hasEdge(int source, int destination);

    /**
     * @brief Adjacency list representing all nodes as nodes and edges as edges.
     *        Each node is mapped to a vector of edges going out from that node.
     */
    std::unordered_map<int, std::vector<Edge>> adjacency_list;
    /**
     * @brief Hashtable with node IDs being mapped to their objects
     */
    std::unordered_map<int, Node> nodes;


    void tsp_backtracking(int curr_pos, std::vector<bool> &visited, int n, int count, double cost,
                          std::vector<int> &path, double &min_cost);

    int getNumNodes();

    double getEdgeWeight(int source, int destination);

    void
    solve_tsp_backtracking_helper(std::vector<int> &visited, double &minDistance, double currentDistance,
                                  int currentNode);

    Edge getEdge(int source, int destination);

    void
    solve_tsp_backtracking_helper(std::vector<int> &visited, double &minDistance, double currentDistance,
                                  int currentNode,
                                  std::vector<int> &currentPath, std::vector<int> &minPath);
};
//
#endif //SRC_GRAPH_H

