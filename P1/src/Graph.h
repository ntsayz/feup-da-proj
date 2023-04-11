//
// Created by ntsayz on 09-03-2023.
//

#include <vector>
#include <unordered_map>
#include <iostream>
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
     int reduced_max_trains_between_stations(const std::string& source, const std::string& destination) const;

    std::vector<Segment> getSegments(const std::string& station_name) const;

    Graph getReducedNetwork(const std::string& source) const;

    std::pair<std::vector<std::pair<std::string, double>>, std::vector<std::pair<std::string, double>>> top_k_municipalities_and_districts(int k);

    int max_trains_between_stations(const std::string &source, const std::string &destination) const;


    std::vector<std::pair<std::string, std::string>> stations_most_trains() const;

    std::vector<std::tuple<std::string, std::string, int>> stations_require_most_trains() const;

    int edmonds_karp_max_flow(const std::string &source, const std::string &destination) const;

    std::unordered_map<Segment, std::vector<std::string>> most_affected_stations_by_segment_failure(std::string source, std::string destination) const;
    std::vector<std::tuple<std::string, std::string, int>> top_k_affected_stations_by_segment_failure(int k);
    int max_trains_between_stations_reduced_connectivity(const std::string &source, const std::string &destination,
                                                         double reduction_factor);
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
