//
// Created by ntsayz on 09-03-2023.
//

#include <vector>
#include <unordered_map>
#include <chrono>
#include <cmath>
#include "Edge.h"
#include "Node.h"
#include "Utility.h"

#ifndef SRC_GRAPH_H
#define SRC_GRAPH_H


class Graph {
public:
    /**
     * @brief Adds a node ID to the graph
     * @param nodeId The ID of the node to be added
     */
    void addNode(int nodeId);

    /**
     * @brief Adds an edge to the graph
     * @param edge The edge to be added
     */
    void addEdge(Edge& edge);

    // Constants for Haversine formula
    const double EARTH_RADIUS_KM = 6371.0;
    const double PI = 3.141592653589793;

    // Function to convert degree to radian
    /**
     * @brief Converts degree to radian
     * @param deg Degree value to convert
     * @return Radian value
     */
    double deg2rad(double deg) const {
        return (deg * PI / 180);
    }

    // Haversine formula to calculate the distance between two points given their latitudes and longitudes
    /**
     * @brief Calculates the Haversine distance between two points on Earth's surface
     * @param lat1 Latitude of the first point
     * @param lon1 Longitude of the first point
     * @param lat2 Latitude of the second point
     * @param lon2 Longitude of the second point
     * @return Haversine distance in kilometers
     */
    double haversine_distance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Applies the Triangular Approximation algorithm to solve the Traveling Salesman Problem
     */
    void triangular_apprx();

    /**
     * @brief Resets the graph to its initial state
     */
    void reset();

    /**
     * @brief Applies the Backtracking algorithm to solve the Traveling Salesman Problem
     */
    void backtracking_tsp();

    /**
     * @brief Fills the node data from the adjacency list
     */
    void fillNodesFromAdjList();

    std::unordered_map<int, Node> node_data;
    /**
     * @brief Sets the current nodes file name
     * @param currNodesfname The file name of the nodes
     */
    void setCurrNodesfname(const std::string& currNodesfname);

    /**
     * @brief Applies the Nearest Neighbor heuristic to solve the Traveling Salesman Problem
     */
    void nearest_neighbor_hrstc();

    /**
     * @brief Applies the Greedy 2-Opt heuristic to solve the Traveling Salesman Problem
     */
    void greedy_2opt_hrstc();

    /**
     * @brief Prints the graph
     */
    void printGraph() const;

    /**
     * @brief Returns a vector of edges going out from a specified node
     * @param nodeId The ID of the node to get the edges for
     * @return A vector of edges going out from the specified node
     */
    std::vector<Edge> getEdgesFromNode(int nodeId) const;

private:
    /**
     * @brief Checks if an edge exists between two nodes
     * @param source The source node ID
     * @param destination The destination node ID
     * @return True if the edge exists, False otherwise
     */
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

    /**
     * @brief Gets the weight of an edge between two nodes
     * @param source The source node ID
     * @param destination The destination node ID
     * @return The weight of the edge
     */
    double getEdgeWeight(int source, int destination);

    /**
     * @brief Gets the edge object between two nodes
     * @param source The source node ID
     * @param destination The destination node ID
     * @return The edge object
     */
    Edge getEdge(int source, int destination);

    /**
     * @brief Helper function for the Backtracking algorithm
     * @param visited List of visited nodes
     * @param minDistance Reference to the minimum distance found
     * @param currentDistance Current distance of the path
     * @param currentNode Current node being visited
     * @param currentPath Current path
     * @param minPath Reference to the minimum path found
     */
    void backtracking_helper(std::vector<int>& visited, double& minDistance, double currentDistance,
                             int currentNode, std::vector<int>& currentPath, std::vector<int>& minPath);

    /**
     * @brief Creates a Minimum Spanning Tree (MST) of the graph
     * @return The MST as an adjacency list
     */
    std::unordered_map<int, std::vector<Edge>> createMST();

    /**
     * @brief Gets the distance between two nodes
     * @param node1 The first node ID
     * @param node2 The second node ID
     * @return The distance between the two nodes
     */
    double getEdgeDistance(int node1, int node2);

    std::string curr_nodesfname;

};

#endif //SRC_GRAPH_H
