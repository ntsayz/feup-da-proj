//
// Created by ntsayz on 09-03-2023.
//

#include <queue>
#include <unordered_set>
#include "Graph.h"

void Graph::addStation(const Station &station) {
    stations[station.getName()] = station;
}

void Graph::addSegment(const Segment &segment) {
    adjacency_list[segment.getSource()].push_back(segment);
}
std::vector<Segment> Graph::getSegments(const std::string& station_name) const {
    // Check if the station exists in the graph
    if (adjacency_list.count(station_name) == 0) {
        return {};
    }

    // Return the segments connected to the station
    return adjacency_list.at(station_name);
}


std::pair<std::vector<std::pair<std::string, double>>, std::vector<std::pair<std::string, double>>> Graph::top_k_municipalities_and_districts(int k) {

    std::unordered_map<std::string, std::string> station_to_municipality;
    std::unordered_map<std::string, std::string> station_to_district;
    for (const auto& [id, station] : stations) {
        station_to_municipality[id] = station.getMunicipality();
        station_to_district[id] = station.getDistrict();
    }

    Graph graph_copy = *this;
    for (auto& [id, edges] : graph_copy.adjacency_list) {
        for (auto& edge : edges) {
            edge.setCapacity(1.0 / edge.getCapacity());
        }
    }


    std::unordered_map<std::string, double> station_traffic_volumes;
    for (const auto& [id, edges] : graph_copy.adjacency_list) {
        double traffic_volume = 0.0;
        for (const auto& edge : edges) {
            traffic_volume += edge.getCapacity();
        }
        station_traffic_volumes[id] = traffic_volume;
    }

    std::unordered_map<std::string, double> municipality_traffic_volumes;
    std::unordered_map<std::string, double> district_traffic_volumes;
    for (const auto& [id, traffic_volume] : station_traffic_volumes) {
        const auto& municipality = station_to_municipality[id];
        const auto& district = station_to_district[id];
        municipality_traffic_volumes[municipality] += traffic_volume;
        district_traffic_volumes[district] += traffic_volume;
    }

    std::vector<std::pair<std::string, double>> top_k_municipalities;
    std::vector<std::pair<std::string, double>> top_k_districts;
    for (const auto& [municipality, traffic_volume] : municipality_traffic_volumes) {
        top_k_municipalities.emplace_back(municipality, traffic_volume);
    }
    std::partial_sort(top_k_municipalities.begin(), top_k_municipalities.begin() + k, top_k_municipalities.end(),
                      [](const auto& lhs, const auto& rhs) {
                          return lhs.second > rhs.second;
                      });
    top_k_municipalities.resize(k);

    for (const auto& [district, traffic_volume] : district_traffic_volumes) {
        top_k_districts.emplace_back(district, traffic_volume);
    }
    std::partial_sort(top_k_districts.begin(), top_k_districts.begin() + k, top_k_districts.end(),
                      [](const auto& lhs, const auto& rhs) {
                          return lhs.second > rhs.second;
                      });
    top_k_districts.resize(k);

    return {top_k_municipalities, top_k_districts};
}

// Currently not working as intended
int Graph::reduced_max_trains_between_stations(const std::string& source, const std::string& destination) const {
    if (stations.find(source) == stations.end() || stations.find(destination) == stations.end()) {
        return 0;
    }

    Graph reducedNetwork = getReducedNetwork(source);

    int max_flow = 0;

    while (true) {
        std::unordered_map<std::string, std::pair<std::string, int>> parent;
        std::queue<std::pair<std::string, int>> searchQueue;
        searchQueue.push({source, INT_MAX});

        while (!searchQueue.empty()) {
            auto current = searchQueue.front();
            searchQueue.pop();

            for (const Segment& segment : reducedNetwork.getSegments(current.first)) {
                std::string next_station = segment.getDestination();
                int next_capacity = segment.getCapacity();

                if (parent.find(next_station) == parent.end() && next_capacity > 0) {
                    parent[next_station] = {current.first, std::min(current.second, next_capacity)};
                    searchQueue.push({next_station, parent[next_station].second});

                    if (next_station == destination) {
                        break;
                    }
                }
            }
        }

        if (parent.find(destination) == parent.end()) {
            break;
        }

        int path_flow = parent[destination].second;
        max_flow += path_flow;

        std::string current = destination;
        while (current != source) {
            std::string prev = parent[current].first;

            // Update edge capacity
            for (Segment& edge : reducedNetwork.adjacency_list[prev]) {
                if (edge.getDestination() == current) {
                    edge.setCapacity(edge.getCapacity() - path_flow);
                    break;
                }
            }

            // Add reverse edge for the residual graph
            bool reverse_edge_exists = false;
            for (Segment& reverse_edge : reducedNetwork.adjacency_list[current]) {
                if (reverse_edge.getDestination() == prev) {
                    reverse_edge.setCapacity(reverse_edge.getCapacity() + path_flow);
                    reverse_edge_exists = true;
                    break;
                }
            }

            if (!reverse_edge_exists) {
                reducedNetwork.adjacency_list[current].push_back(Segment(current, prev, path_flow, ""));
            }

            current = prev;
        }
    }

    return max_flow;
}


Graph Graph::getReducedNetwork(const std::string& source) const {
    Graph reduced_network;
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    visited.insert(source);
    q.push(source);
    while (!q.empty()) {
        const std::string& node = q.front();
        q.pop();
        if (adjacency_list.count(node) == 0) {
            continue;  // key not present in adjacency list
        }
        reduced_network.addStation(stations.at(node));
        for (const Segment& edge : adjacency_list.at(node)) {
            if (visited.count(edge.getDestination()) == 0 && edge.getCapacity() > 0) {
                reduced_network.addStation(stations.at(edge.getDestination()));
                reduced_network.addSegment(edge);
                visited.insert(edge.getDestination());
                q.push(edge.getDestination());
            }
        }
    }
    return reduced_network;
}

std::vector<Segment> Graph::getSegmentsFromStation(const std::string station) const {
    // Find the station in the adjacency list
    auto it = adjacency_list.find(station);
    if (it == adjacency_list.end()) {
        // Station not found, return an empty vector
        return std::vector<Segment>();
    } else {
        // Return the vector of segments going out from the station
        return it->second;
    }
}


std::vector<Segment> Graph::getSegmentsToStation(const std::string station) const {
    std::vector<Segment> segments_to_station;
    std::vector<Segment> segments = getSegments(station);
    for(auto s: segments){
        if(s.getDestination() == station){
            segments_to_station.push_back(s);
        }
    }
    return segments_to_station;
}


int Graph::max_trains_between_stations(const std::string& source, const std::string& destination) const {
    // Initialize the minimum capacity to a large number
    int min_capacity = INT_MAX;

    // Initialize the visited set and queue for BFS
    std::unordered_set<std::string> visited;
    std::queue<std::pair<std::string, int>> q;
    q.push({source, INT_MAX});

    // Perform BFS until the destination station is found or the queue is empty
    while (!q.empty()) {
        // Get the next station and its minimum capacity seen so far
        auto [current, capacity] = q.front();
        q.pop();

        // Skip if the station has already been visited
        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);

        // Update the minimum capacity seen for the current station
        min_capacity = std::min(min_capacity, capacity);

        // Stop BFS if the destination station is found
        if (current == destination) {
            break;
        }

        // Add the adjacent stations to the queue
        for (const auto& seg : getSegmentsFromStation(current)) {
            q.push({seg.getDestination(), seg.getCapacity()});
        }
    }

    // Return the minimum capacity seen for the path from the source to the destination station
    return min_capacity;
}




