//
// Created by ntsayz on 09-03-2023.
//

#include <queue>
#include <unordered_set>
#include <random>
#include "Graph.h"

void Graph::printGraph() const {
    auto size = adjacency_list.size();

    for (const auto& node : adjacency_list) {
        Utility::safe_print("Node " + std::to_string(node.first) + " is connected to:");
        for (const auto& edge : node.second) {
            Utility::safe_print("Node "+ std::to_string(edge.getDestination()) + " with a distance of " + std::to_string(edge.getDistance()));
        }
        Utility::safe_print("-----");
    }
    Utility::safe_print("This has " + std::to_string(size) + " nodes");


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

void Graph::addNode(int nodeId) {
    nodes.emplace(nodeId, Node(nodeId));
}

void Graph::addEdge(Edge &edge) {
    adjacency_list[edge.getSource()].push_back(edge);
    Edge reverseEdge = Edge(edge.getDestination(), edge.getSource(), edge.getDistance());
    adjacency_list[reverseEdge.getSource()].push_back(reverseEdge);
}
void Graph::fillNodesFromAdjList() {
    //this will not be pretty code
    for (const auto& entry : adjacency_list) {
        if (nodes.find(entry.first) == nodes.end()) {
            nodes[entry.first] = Node(entry.first);
        }
        for (const auto& edge : entry.second) {
            if (nodes.find(edge.getDestination()) == nodes.end()) {
                nodes[edge.getDestination()] = Node(edge.getDestination());
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

void Graph::backtracking_tsp() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> visited;
    double minDistance = std::numeric_limits<double>::max();
    double currentDistance = 0.0;
    std::vector<int> currentPath;
    std::vector<int> minPath;

    int startingNode = 0;
    visited.push_back(startingNode);
    currentPath.push_back(startingNode);

    backtracking_helper(visited, minDistance, currentDistance, startingNode, currentPath, minPath);

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    std::cout << "Minimum Path: ";
    for (const auto& node : minPath) {
        std::cout << node << " -> ";
    }
    std::cout << "\nTotal Distance: " << minDistance << std::endl;
    int choice;
    std::cin >> choice;
}


void Graph::backtracking_helper(std::vector<int>& visited, double& minDistance, double currentDistance, int currentNode, std::vector<int>& currentPath, std::vector<int>& minPath) {

    if (visited.size() == nodes.size()) {
        // check se o current path e better than the minimum path distance found ate agora
        if (currentDistance + getEdge(currentNode, 0).getDistance() < minDistance) {
            minDistance = currentDistance + getEdge(currentNode, 0).getDistance();
            minPath = currentPath;
            minPath.push_back(0);
        }
        return;
    }

    // itera over all nodes nao visitados
    for (const auto& edge : adjacency_list[currentNode]) {
        int nextNode = edge.getDestination();


        if (std::find(visited.begin(), visited.end(), nextNode) == visited.end()) {

            visited.push_back(nextNode);
            currentPath.push_back(nextNode);


            currentDistance += edge.getDistance();


            backtracking_helper(visited, minDistance, currentDistance, nextNode, currentPath, minPath);


            visited.pop_back();
            currentPath.pop_back();
            currentDistance -= edge.getDistance();
        }
    }
}

void Graph::triangular_apprx() {
    auto start = std::chrono::high_resolution_clock::now();
    // create MST
    auto mst = createMST();

    // traverse the MST
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
    // se a edge nao estiver na adj calcula a distancia a usar haversine (this is important)
    return  haversine_distance(node_data[node1].getLatitude(), node_data[node1].getLongitude(),
                                         node_data[node2].getLatitude(), node_data[node2].getLongitude());

}

std::unordered_map<int, std::vector<Edge>> Graph::createMST() {
    std::unordered_map<int, std::vector<Edge>> mst;
    std::priority_queue<Edge, std::vector<Edge>,std::greater<>> minHeap;  // min-heap for the edges
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




void Graph::nearest_neighbor_hrstc() {
    auto start = std::chrono::high_resolution_clock::now();
    if (adjacency_list.empty()) {
        return;
    }

    int startNode = 0;
    std::vector<int> path;
    std::unordered_set<int> visited;
    double totalDistance = 0.0;

    int currentNode = startNode;
    visited.insert(currentNode);
    path.push_back(currentNode);

    while (visited.size() < adjacency_list.size()) {
        int nextNode = -1;
        double minDistance = INFINITY;

        //find the closest node nao visitado
        for (const auto& edge : adjacency_list[currentNode]) {
            if (visited.find(edge.getDestination()) == visited.end()) {
                double distance = edge.getDistance();
                if (distance < minDistance) {
                    nextNode = edge.getDestination();
                    minDistance = distance;
                }
            }
        }


        if (nextNode == -1) {
            break;
        }

        visited.insert(nextNode);
        path.push_back(nextNode);
        totalDistance += minDistance;  // add the distance to the total
        currentNode = nextNode;
    }

    // if the last node in the path is not the start node
    if (currentNode != startNode) {
        // find the closest node that has a direct edge to the start node
        int nextNode = -1;
        double minDistance = INFINITY;
        for (const auto& node : path) {
            auto iter = find_if(adjacency_list[node].begin(), adjacency_list[node].end(), [&startNode](const Edge& edge) {
                return edge.getDestination() == startNode;
            });
            if (iter != adjacency_list[node].end()) {
                if (iter->getDistance() < minDistance) {
                    nextNode = node;
                    minDistance = iter->getDistance();
                }
            }
        }
        if (nextNode != -1) {
            totalDistance += getEdgeWeight(currentNode, nextNode) + minDistance;
            path.push_back(nextNode);
        }
        path.push_back(startNode);
    }

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";


    Utility::safe_print("Approximate TSP path using Nearest Neighbor heuristic:");
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i] ;
        if (i != path.size() - 1) {
            std::cout <<" -> ";
        }
    }
    Utility::safe_print("\nTotal distance: " + std::to_string(totalDistance));
    int choice;
    std::cin >> choice;
}


void Graph::greedy_2opt_hrstc() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<bool> visited(nodes.size(), false);
    std::vector<int> path;
    double total_distance = 0.0;

    int current_node = 0;
    path.push_back(current_node);
    visited[current_node] = true;

    while (path.size() < nodes.size()) {
        double min_distance = std::numeric_limits<double>::max();
        int closest_node;

        for (const auto& edge : adjacency_list[current_node]) {
            if (!visited[edge.getDestination()] && edge.getDistance() < min_distance) {
                min_distance = edge.getDistance();
                closest_node = edge.getDestination();
            }
        }

        current_node = closest_node;
        path.push_back(current_node);
        visited[current_node] = true;
        total_distance += min_distance;
    }


    total_distance += getEdge(current_node, 0).getDistance();
    path.push_back(0);

    // apply the 2-opt hrstc to improve the tour
    bool improvement = true;
    while (improvement) {
        improvement = false;

        for (int i = 0; i < path.size() - 2; i++) {
            for (int j = i + 2; j < path.size() - 1; j++) {
                double old_distance = getEdge(path[i], path[i + 1]).getDistance() + getEdge(path[j], path[j + 1]).getDistance();
                double new_distance = getEdge(path[i], path[j]).getDistance() + getEdge(path[i + 1], path[j + 1]).getDistance();

                if (new_distance < old_distance) {
                    std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                    total_distance = total_distance - old_distance + new_distance; // Update the total distance
                    improvement = true;
                }
            }
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    for (const auto& node : path)
        std::cout << node << " ";
    std::cout << std::endl;

    std::cout << "Total distance: " << total_distance << std::endl;
    int choice;
    std::cin >> choice;
}











