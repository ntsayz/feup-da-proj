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
int Graph::max_trains_between_stations(const std::string& source, const std::string& destination) const {
    // Check if source and destination stations exist
    if (stations.find(source) == stations.end() || stations.find(destination) == stations.end()) {
        return 0;
    }

    // Get the reduced network
    Graph reducedNetwork = getReducedNetwork(source);

    // Initialize visited stations set
    std::unordered_set<std::string> visited;

    // Initialize the search queue with the source station and its capacity
    std::queue<std::pair<std::string, int>> searchQueue;
    searchQueue.push({source, INT_MAX});

    // Breadth-first search
    while (!searchQueue.empty()) {
        auto current = searchQueue.front();
        searchQueue.pop();

        // If we reached the destination station, return the minimum capacity along the path
        if (current.first == destination) {
            return current.second;
        }


        visited.insert(current.first);


        for (const Segment& segment : reducedNetwork.getSegments(current.first)) {
            std::string next_station = segment.getDestination();
            int next_capacity = segment.getCapacity();

            // If the station has not been visited and has capacity, add it to the queue
            if (visited.find(next_station) == visited.end() && next_capacity > 0) {
                searchQueue.push({next_station, std::min(current.second, next_capacity)});
            }
        }
    }

    // No path found between the stations
    return 0;
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
            if (visited.count(edge.getDestination()) == 0) {
                reduced_network.addStation(stations.at(edge.getDestination()));
                reduced_network.addSegment(edge);
                visited.insert(edge.getDestination());
                q.push(edge.getDestination());
            }
        }
    }
    return reduced_network;
}

