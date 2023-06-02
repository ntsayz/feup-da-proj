//
// Created by ntsayz on 09-03-2023.
//

#include <queue>
#include <unordered_set>
#include "Graph.h"


std::vector<int> findEulerianTour(std::unordered_map<int, std::vector<Edge>> map);

std::vector<int> findHamiltonianPath(std::vector<int> vector1);

double calculatePathDistance(std::vector<int> vector1);

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
        std::cout << node << " -> ";
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
        if(curr_nodesfname != "no files chosen"){
            totalDistance += getEdgeDistance(node1, node2);
        }else{
            totalDistance += getEdge(node1, node2).getDistance();
        }

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    Utility::safe_print("Approximate TSP path using 2-approximation based on triangular inequality (MST):");
    for (const auto& node : traversal) {
        std::cout << node << " -> ";
    }
    Utility::safe_print("\nTotal distance: "+ std::to_string(totalDistance));
    int i ;
    std::cin >>i;
}

double Graph::getEdgeDistance(int node1, int node2) {
    if (adjacency_list.count(node1)) {
        for(const auto& edge : adjacency_list[node1]){
            if(edge.getDestination() == node2)
                return edge.getDistance();
        }
    }
    // If edge is not in the adjacency list, calculate distance and create an edge
    return  haversine_distance(node_data[node1].getLatitude(), node_data[node1].getLongitude(),
                                         node_data[node2].getLatitude(), node_data[node2].getLongitude());

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

double Graph::haversine_distance(double lat1, double lon1, double lat2, double lon2) {
lat1 = deg2rad(lat1);
lon1 = deg2rad(lon1);
lat2 = deg2rad(lat2);
lon2 = deg2rad(lon2);

double dlat = lat2 - lat1;
double dlon = lon2 - lon1;

double a = pow(sin(dlat / 2), 2) +
           cos(lat1) * cos(lat2) *
           pow(sin(dlon / 2), 2);

double c = 2 * atan2(sqrt(a), sqrt(1 - a));

return EARTH_RADIUS_KM * c;
}

void Graph::setCurrNodesfname(const std::string &currNodesfname) {
    curr_nodesfname = currNodesfname;
}

void Graph::solve_tsp_christofides() {
    auto start = std::chrono::high_resolution_clock::now();

    // Step 1: Create a minimum spanning tree (MST) of the graph
    std::unordered_map<int, std::vector<Edge>> mst = createMST();

    // Step 2: Find the set of vertices with odd degrees
    std::vector<int> oddDegreeNodes = findOddDegreeNodes();

    // Step 3: Create a subgraph induced by the odd degree vertices
    std::unordered_map<int, std::vector<Edge>> subgraph = createSubgraph(oddDegreeNodes);

    // Step 4: Find the minimum spanning perfect matching of the subgraph
    std::unordered_map<int, std::vector<Edge>> matching = findMinimumSpanningPerfectMatching(subgraph);

    // Step 5: Combine the MST and the matching edges to form a multigraph
    for (const auto& node : matching) {
        for (const auto& edge : node.second) {
            mst[edge.getSource()].push_back(edge);
            mst[edge.getDestination()].push_back(edge);
        }
    }

    // Step 6: Find an Eulerian tour in the multigraph
    std::vector<int> eulerianTour = findEulerianTour(mst);

    // Step 7: Find a Hamiltonian path from the Eulerian tour
    std::vector<int> hamiltonianPath = findHamiltonianPath(eulerianTour);

    // Step 8: Calculate the total distance of the Hamiltonian path
    double minDistance = calculatePathDistance(hamiltonianPath);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the results
    Utility::safe_print("TSP (Christofides) Solution:");
    Utility::safe_print(std::string("Path: ") + Utility::vectorToString(hamiltonianPath));
    Utility::safe_print("Total Distance: " + std::to_string(minDistance));
    Utility::safe_print("Time taken: " + std::to_string(duration.count()) + " milliseconds");
}

double calculatePathDistance(std::vector<int> vector1) {
    return 0;
}

std::vector<int> findHamiltonianPath(std::vector<int> vector1) {
    return std::vector<int>();
}

std::vector<int> findEulerianTour(std::unordered_map<int, std::vector<Edge>> map) {
    return std::vector<int>();
}

std::vector<int> Graph::findOddDegreeNodes() {
    std::vector<int> oddDegreeNodes;

    for (const auto& node : nodes) {
        int nodeId = node.first;
        if (adjacency_list[nodeId].size() % 2 != 0) {
            oddDegreeNodes.push_back(nodeId);
        }
    }

    return oddDegreeNodes;
}

std::unordered_map<int, std::vector<Edge>> Graph::createSubgraph(const std::vector<int>& oddDegreeNodes) {
    std::unordered_map<int, std::vector<Edge>> subgraph;

    for (int node : oddDegreeNodes) {
        subgraph[node] = adjacency_list[node];
    }

    return subgraph;
}
struct CompareEdge {
    bool operator()(const Edge& edge1, const Edge& edge2) {
        return edge1.getDistance() > edge2.getDistance();
    }
};


std::unordered_map<int, std::vector<Edge>> Graph::findMinimumSpanningPerfectMatching(const std::unordered_map<int, std::vector<Edge>>& subgraph) {
    std::unordered_map<int, std::vector<Edge>> matching;

    std::unordered_set<int> visited;
    std::priority_queue<Edge, std::vector<Edge>, CompareEdge> pq;

    // Add all edges from the subgraph to the priority queue
    for (const auto& node : subgraph) {
        for (const auto& edge : node.second) {
            pq.push(edge);
        }
    }

    // Construct the minimum spanning perfect matching
    while (!pq.empty()) {
        Edge currentEdge = pq.top();
        pq.pop();

        int source = currentEdge.getSource();
        int destination = currentEdge.getDestination();

        // Check if adding the edge will form a cycle
        if (visited.find(source) != visited.end() || visited.find(destination) != visited.end())
            continue;

        // Add the edge to the matching
        matching[source].push_back(currentEdge);
        matching[destination].push_back(currentEdge);

        visited.insert(source);
        visited.insert(destination);
    }

    return matching;
}







