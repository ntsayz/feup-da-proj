//
// Created by ntsayz on 09-03-2023.
//

#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <limits>
#include <string>
#include "Segment.h"
#include "Station.h"
#ifndef SRC_GRAPH_H
#define SRC_GRAPH_H

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};


class Graph {
public:
    /**
     * @brief Adds a station to the graph
     * @param station The station to be added
     */
    void addStation(const Station& station);
    /**
     * @brief Adds a segment to the graph
     * @param segment The segment to be added
     */
    void addSegment(const Segment& segment);
    /**
     * @brief Returns a vector of all segments going out from a specified station
     * @param station The station to get the segments for
     * @return A vector of all segments going out from the specified station
     */
    std::vector<Segment> getSegmentsFromStation(const std::string station) const;
    /**
     * @brief Returns a vector of all segments going into a specified station
     * @param station The station to get the segments for
     * @return A vector of all segments going into the specified station
     */
    std::vector<Segment> getSegmentsToStation(const std::string station) const;
    /**
     * @brief Returns the number of segments going out from a specified station
     * @param station The station to get the segments for
     * @return The number of segments going out from the specified station
     */
    int numSegmentsFromStation(const std::string station) const;
    /**
     * @brief Returns the number of segments going into a specified station
     * @param station The station to get the segments for
     * @return The number of segments going into the specified station
     */
    int numSegmentsToStation(const std::string station) const;
        /**
     * @brief Calculates the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity
     * @param start_station The starting station
     * @param end_station The ending station
     * @return The maximum number of trains that can simultaneously travel between the two stations in the reduced network
     */

    [[nodiscard]] std::vector<Segment> getSegments(const std::string& station_name) const;

        /**
     * @brief Finds the top k municipalities and districts with the highest traffic volume
     * @param k Number of top municipalities and districts to be returned.
     * @return A pair of two vectors: the first vector contains the top k municipalities with the highest traffic volume,
     *       and the second with the districts
     */
    std::pair<std::vector<std::pair<std::string, double>>, std::vector<std::pair<std::string, double>>> top_k_municipalities_and_districts(int k);

    /**
     * @brief Computes the maximum number of trains that can simultaneously travel between two stations.
     * @param source The source station.
     * @param destination The destination station.
     * @return The maximum number of trains that can simultaneously travel between the two stations.
     * @note Time complexity: O(V * E^2) using Edmonds-Karp algorithm.
     */
    int max_trains_between_stations(const std::string &source, const std::string &destination) const;

    /**
     * @brief Finds the stations that require the most number of trains when taking full advantage of the network capacity.
     * @return A vector of tuples, each containing two station names and the number of trains required between them.
     * @note Time complexity: O(V^3) using a modified version of Floyd-Warshall algorithm.
     */
    std::vector<std::tuple<std::string, std::string, int>> stations_require_most_trains() const;

    /**
     * @brief Computes the maximum flow between two stations using the Edmonds-Karp algorithm.
     * @param source The source station.
     * @param destination The destination station.
     * @return The maximum flow between the two stations.
     * @note Time complexity: O(V * E^2).
     */
    int edmonds_karp_max_flow(const std::string &source, const std::string &destination) const;
    /**
     * @brief Computes the top k segments that, when removed, cause the most number of affected stations.
     * @param k The number of segments to be returned.
     * @return A vector of tuples, each containing a source station, a destination station, and the number of affected stations for that segment.
     */
    std::vector<std::tuple<std::string, std::string, int>> top_k_affected_stations_by_segment_failure(int k);

    /**
     * @brief Computes the maximum number of trains that can simultaneously travel between two stations with reduced connectivity.
     * @param source The source station.
     * @param destination The destination station.
     * @param reduction_factor The probability of removing a segment.
     * @return The maximum number of trains that can simultaneously travel between the two stations with reduced connectivity.
     * @note Time complexity: O(V * E^2) using Edmonds-Karp algorithm.
     */
    int max_trains_between_stations_reduced_connectivity(const std::string &source, const std::string &destination, double reduction_factor);

    /**
     * @brief Computes the maximum number of trains that can be at a station at the same time.
     * @param station The station in question.
     * @return The maximum number of trains that can be at the station at the same time.
     * @note Time complexity: O(V^2 * E^2) using Edmonds-Karp algorithm.
     */
    int max_trains_at_station(const std::string &station) const;
    /**
     * @brief Computes the shortest path from the source station to all other stations using Dijkstra's algorithm.
     * @param source The source station.
     * @return An unordered map with station names as keys and the shortest path distance from the source station as values.
     * @note Time complexity: O(V + E * log(V)) using a priority queue.
     */
    std::unordered_map<std::string, double> dijkstra_shortest_path(const std::string& source) const;

    /**
     * @brief Computes the maximum number of trains that can simultaneously travel between two stations with minimum cost for the company.
     * @param source The source station.
     * @param destination The destination station.
     * @return The maximum number of trains that can simultaneously travel between the two stations with minimum cost for the company.
     * @note Time complexity: O(V * E^2) using a mixture of Dijkstra (w/PQ) and the Edmonds-Karp algorithm
     */
    int max_trains_with_min_cost(const std::string &source, const std::string &destination);

private:
    /**
     * @brief Adjacency list representing all stations as nodes and segments as edges.
     *        Each station is mapped to a vector of segments going out from that station.
     */
    std::unordered_map<std::string, std::vector<Segment>> adjacency_list;
    /**
     * @brief Hashtable with station IDs being mapped to their objects
     */
    std::unordered_map<std::string, Station> stations;


    void removeSegment(const std::string &source, const std::string &destination);

    std::unordered_map<std::pair<std::string, std::string>, int, PairHash> all_pairs_max_trains_floyd_warshall() const;

    Graph generate_reduced_connectivity_graph(double reduction_factor) const;


};


#endif //SRC_GRAPH_H
