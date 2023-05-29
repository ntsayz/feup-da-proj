//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Manager.h"

void Manager::run() {
    if(!load_data()){
        return;
    }
    main_menu();

}
bool Manager::load_data() {
    std::string nodes_fname = "no file chosen" , edges_fname = "no file chosen";
    localSession = true;
    while(localSession){
        Utility::clear_screen();
        switch (Menu::DataLoader(nodes_fname, edges_fname)) {
            case 1:
                nodes_fname = "." , edges_fname = "../dataset/network.csv"; // TODO:  Mudar isto
                break;
            case 2:
                Utility::get_filenames(nodes_fname, edges_fname);
                break;
            case 9:
                localSession = false;
        }
    }
    /*
    std::printf("Loading data...");
    std::vector<Node> stationsVEC = Utility::loadDataFromCSV<Node>(nodes_fname);
    std::vector<Edge> segmentsVEC = Utility::loadDataFromCSV<Edge>(edges_fname);

    for(const auto& station: stationsVEC){
        railway_network.addStation(station);
        municipalities[station.getMunicipality()].push_back(station);
        districts[station.getDistrict()].push_back(station);
    }
    for(const auto& segment: segmentsVEC){
        railway_network.addSegment(segment);
    }

    std::printf("\n%zu Municipalities |",municipalities.size());
    std::printf(" %zu Districts |",districts.size());
    std::printf(" %zu Stations \n", stationsVEC.size());*/
    return true;
}

void Manager::main_menu(){
    globalSession = true;
    while (globalSession){
        Utility::clear_screen();
        switch (Menu::Main()) {
            case 1:
                std::printf("Nothing to show here yet");
                break;
            case 2:
                std::printf("Don't look for shit you know its not there sir");
                break;
            case 9:
                globalSession = false;
        }
    }
}






