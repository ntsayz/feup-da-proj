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

// Add a new data member to store the node data
    std::unordered_map<int, Node> node_data;

// Function to convert degree to radian
    double deg2rad(double deg) const {
        return (deg * PI / 180);
    }

// Haversine formula to calculate the distance between two points given their latitudes and longitudes
    double haversine_distance(double lat1, double lon1, double lat2, double lon2);

    void solve_tsp_2approximation();


    void reset();

    void solve_tsp_backtracking();

    void fillNodesFromAdjList();

    void solve_tsp_christofides();

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

    double getEdgeWeight(int source, int destination);

    Edge getEdge(int source, int destination);

    void
    solve_tsp_backtracking_helper(std::vector<int> &visited, double &minDistance, double currentDistance,
                                  int currentNode,
                                  std::vector<int> &currentPath, std::vector<int> &minPath);

    std::unordered_map<int, std::vector<Edge>> createMST();

    std::unordered_map<int, std::vector<Edge>>
    findMinimumSpanningPerfectMatching(const std::unordered_map<int, std::vector<Edge>> &subgraph);

    std::unordered_map<int, std::vector<Edge>> createSubgraph(const std::vector<int> &oddDegreeNodes);

    std::vector<int> findOddDegreeNodes();

    double getEdgeDistance(int node1, int node2);

    std::string curr_nodesfname;
public:
    void setCurrNodesfname(const std::string &currNodesfname);

    double calculatePathDistance(std::vector<int> &path);

    std::vector<int> findHamiltonianPath(std::vector<int> &eulerianTour);

    std::vector<int> findEulerianTour(std::unordered_map<int, std::vector<Edge>> &graph);

    void solve_tsp_nearest_neighbor();

    void solve_tsp_nearest_neighbor2();

    void greedy_2opt_tsp();

    void printGraph() const;

    std::vector<Edge> getEdgesFromNode(int nodeId) const;
};
//
#endif //SRC_GRAPH_H

