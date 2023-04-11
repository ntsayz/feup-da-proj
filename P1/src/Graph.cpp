//
// Created by ntsayz on 09-03-2023.
//

#include <queue>
#include <unordered_set>
#include "Graph.h"

void Graph::addStation(const Station &station) {
    stations[station.getName()] = station;
}
void Graph::removeSegment(const std::string& source, const std::string& destination) {
    // Remove the segment from the adjacency list
    auto &segments = adjacency_list[source];
    segments.erase(std::remove_if(segments.begin(), segments.end(), [&](const Segment &seg) {
        return seg.getDestination() == destination;
    }), segments.end());
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

// O(n^2)
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

//
int Graph::max_trains_between_stations_reduced_connectivity(const std::string& source, const std::string& destination, double reduction_factor) {
    Graph reduced_graph = generate_reduced_connectivity_graph(reduction_factor);
    return reduced_graph.edmonds_karp_max_flow(source, destination);
}

Graph Graph::generate_reduced_connectivity_graph(double reduction_factor) const {
    Graph reduced_graph(*this); // Create a copy of the original graph

    for (const auto& source : reduced_graph.adjacency_list) {
        for (const auto& segment : source.second) {
            if (static_cast<double>(rand()) / RAND_MAX < reduction_factor) {
                reduced_graph.removeSegment(segment.getSource(), segment.getDestination());
            }
        }
    }

    return reduced_graph;
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

// O(n^3) -- Floyd-Warshall (altered)
std::vector<std::tuple<std::string, std::string, int>> Graph::stations_require_most_trains() const {
    std::unordered_map<std::string, int> station_indices;
    int index = 0;
    for (const auto& station : stations) {
        station_indices[station.first] = index++;
    }

    int num_stations = stations.size();
    std::vector<std::vector<int>> max_flow(num_stations, std::vector<int>(num_stations, 0));

    for (const auto& source : adjacency_list) {
        for (const auto& segment : source.second) {
            int u = station_indices[source.first];
            int v = station_indices[segment.getDestination()];
            max_flow[u][v] = segment.getCapacity();
        }
    }

    for (int k = 0; k < num_stations; k++) {
        for (int i = 0; i < num_stations; i++) {
            for (int j = 0; j < num_stations; j++) {
                max_flow[i][j] = std::max(max_flow[i][j], std::min(max_flow[i][k], max_flow[k][j]));
            }
        }
    }

    std::vector<std::tuple<std::string, std::string, int>> result;
    int global_max_flow = 0;

    for (const auto& source : station_indices) {
        for (const auto& destination : station_indices) {
            if (source.first != destination.first) {
                int flow = max_flow[source.second][destination.second];
                if (flow > global_max_flow) {
                    global_max_flow = flow;
                    result.clear();
                    result.push_back({source.first, destination.first, flow});
                } else if (flow == global_max_flow) {
                    result.push_back({source.first, destination.first, flow});
                }
            }
        }
    }

    return result;
}

int Graph::edmonds_karp_max_flow(const std::string& source, const std::string& destination) const {
    int max_flow = 0;

    // Create a residual graph and fill it with the capacity values of the original graph
    std::unordered_map<std::string, std::unordered_map<std::string, int>> residual_graph;
    for (const auto& src : adjacency_list) {
        for (const auto& segment : src.second) {
            residual_graph[src.first][segment.getDestination()] = segment.getCapacity();
        }
    }

    // BFS
    auto bfs_augmenting_path = [&residual_graph, &source, &destination](std::unordered_map<std::string, std::string>& parent) {
        std::unordered_set<std::string> visited;
        std::queue<std::string> q;

        q.push(source);
        visited.insert(source);

        while (!q.empty()) {
            std::string current = q.front();
            q.pop();

            for (const auto& next : residual_graph[current]) {
                if (next.second > 0 && visited.find(next.first) == visited.end()) {
                    parent[next.first] = current;
                    visited.insert(next.first);
                    q.push(next.first);

                    if (next.first == destination) {
                        return true;
                    }
                }
            }
        }

        return false;
    };

    // Edmonds-Karp algorithm
    std::unordered_map<std::string, std::string> parent;
    while (bfs_augmenting_path(parent)) {
        int path_flow = INT_MAX;

        // Find the minimum capacity along the augmenting path
        for (std::string v = destination; v != source; v = parent[v]) {
            std::string u = parent[v];
            path_flow = std::min(path_flow, residual_graph[u][v]);
        }

        // Update the residual graph capacities
        for (std::string v = destination; v != source; v = parent[v]) {
            std::string u = parent[v];
            residual_graph[u][v] -= path_flow;
            residual_graph[v][u] += path_flow;
        }

        // Update the maximum flow
        max_flow += path_flow;
    }

    return max_flow;
}


std::vector<std::tuple<std::string, std::string, int>> Graph::top_k_affected_stations_by_segment_failure(int k) {
    // Compute all pairs max trains using Floyd Warshall
    auto all_pairs_max_trains = all_pairs_max_trains_floyd_warshall();

    // Create a vector to store the results
    std::vector<std::tuple<std::string, std::string, int>> result;
    int c = 0;
    // Iterate through all segments
    for (const auto& source : adjacency_list) {
        std::cout << c;
        c++;
        for (const auto& seg : source.second) {
            // Temporarily remove the segment
            removeSegment(seg.getSource(), seg.getDestination());

            // Compute all pairs max trains after segment removal
            auto all_pairs_max_trains_after_removal = all_pairs_max_trains_floyd_warshall();

            // Calculate the total affected stations for the removed segment
            int total_affected_stations = 0;
            for (const auto& source : stations) {
                for (const auto& destination : stations) {
                    if (all_pairs_max_trains[{source.first, destination.first}] > all_pairs_max_trains_after_removal[{source.first, destination.first}])
                    {
                        total_affected_stations++;
                    }
                }
            }

            // Re-add the segment
            addSegment(seg);

            // Store the result
            result.push_back(std::make_tuple(seg.getSource(), seg.getDestination(), total_affected_stations));
        }
    }

    // Sort the result by the number of affected stations in descending order
    std::sort(result.begin(), result.end(), [](const std::tuple<std::string, std::string, int>& a, const std::tuple<std::string, std::string, int>& b) {
        return std::get<2>(a) > std::get<2>(b);
    });

    // Resize the result vector to contain only the top-k elements
    if (result.size() > k) {
        result.resize(k);
    }

    return result;
}


std::unordered_map<std::pair<std::string, std::string>, int, PairHash> Graph::all_pairs_max_trains_floyd_warshall() const {
    std::unordered_map<std::string, int> station_indices;
    int index = 0;
    for (const auto& station : stations) {
        station_indices[station.first] = index++;
    }

    int num_stations = stations.size();
    std::vector<std::vector<int>> max_flow(num_stations, std::vector<int>(num_stations, 0));

    for (const auto& source : adjacency_list) {
        for (const auto& segment : source.second) {
            int u = station_indices[source.first];
            int v = station_indices[segment.getDestination()];
            max_flow[u][v] = segment.getCapacity();
        }
    }

    for (int k = 0; k < num_stations; k++) {
        for (int i = 0; i < num_stations; i++) {
            for (int j = 0; j < num_stations; j++) {
                max_flow[i][j] = std::max(max_flow[i][j], std::min(max_flow[i][k], max_flow[k][j]));
            }
        }
    }

    std::unordered_map<std::pair<std::string, std::string>, int, PairHash> result;
    for (const auto& src : station_indices) {
        for (const auto& dest : station_indices) {
            if (src.first != dest.first) {
                result[{src.first, dest.first}] = max_flow[src.second][dest.second];
            }
        }
    }

    return result;
}








