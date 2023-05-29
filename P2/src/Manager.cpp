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
    bool hasLabel = false;
    localSession = true;
    while(localSession){
        Utility::clear_screen();
        switch (Menu::DataLoader(nodes_fname, edges_fname)) {
            case 1:
                edges_fname = "../dataset/Toy-Graphs/shipping.csv";
                break;
            case 2:
               // Utility::get_filenames(nodes_fname, edges_fname);
                edges_fname = "../dataset/Toy-Graphs/stadiums.csv";
                break;
            case 3:
                hasLabel = true;
                edges_fname = "../dataset/Toy-Graphs/tourism.csv";
                break;
            // TODO: Adicionar outros ficheiros
            case 9:
                localSession = false;
                break;
        }
    }

    std::vector<Edge> edgesVEC = Utility::loadDataFromCSV<Edge>(edges_fname,hasLabel);

    if(nodes_fname != "no file chosen"){
        std::vector<Node> nodesVEC = Utility::loadDataFromCSV<Node>(nodes_fname,hasLabel);
        for(const auto& node: nodesVEC){
            //graph.addNode(node);
            // municipalities[station.getMunicipality()].push_back(station);
            //districts[station.getDistrict()].push_back(station);
        }

    }

    for(const auto& edge: edgesVEC){
        graph.addEdge(edge);
    }

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






