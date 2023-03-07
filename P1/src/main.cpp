#include <iostream>
#include "Manager.h"

int main() {
    Manager manager;
    manager.run();
    return 0;
}


/**

    @mainpage Portugal Railway - Railway Management Application
    @section intro_sec Introduction
    -write bullshit here-
    @section features_sec Features
        - feature#1
        - feature#2
        - feature#3
    @section data_sec Data
        PR uses data from several CSV files to populate its database of the railway network. These files should be placed in the /dataset subdirectory. The required files are:
        network.csv: Contains information about the different connections between stations in the network (Station_A,Station_B,Capacity,Service)
        stations.csv: Contains information about different stations (Name,District,Municipality,Township,Line)

*/