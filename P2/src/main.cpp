#include <iostream>
#include "Manager.h"

int main() {
    Manager manager;
    manager.run();
    return 0;
}


/**
    @mainpage Routing Algorithms for Ocean Shipping and Urban Deliveries
    @section intro_sec Introduction
    This application is designed to provide routing algorithms for ocean shipping and urban deliveries. It aims to optimize the delivery routes and minimize transportation costs. The algorithms implemented in this application can be used to efficiently plan the transportation of goods and optimize the delivery process.

    @section features_sec Features
    - Nearest Neighbor TSP Algorithm: This algorithm approximates the Traveling Salesman Problem (TSP) by selecting the nearest unvisited neighbor at each step to construct a tour.
    - Greedy 2-opt TSP Algorithm: This algorithm improves an initial tour by iteratively swapping pairs of edges to reduce the total distance.
    - Triangular Approximation Algorithm: This algorithm creates a minimum spanning tree (MST) and traverses it to construct an approximate TSP tour. It uses the triangular inequality property to estimate the distances.
    - Backtracking TSP Algorithm: This algorithm exhaustively explores all possible paths using a backtracking approach to find the optimal TSP tour.

    @section data_sec Data

*/