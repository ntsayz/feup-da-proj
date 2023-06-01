//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Manager.h"
#include "Graph.h"
#include "Edge.h"

void Manager::run() {
    main_menu();

}


void Manager::main_menu(){
    globalSession = true;
    while (globalSession){
        Utility::clear_screen();
        switch (Menu::Main()) {
            case 1:
                load_data();
                break;
            case 2:
                graph.printGraph();
                break;
            case 9:
                globalSession = false;
                break;
        }
    }
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
                edges_fname = "../dataset/Toy-Graphs/stadiums.csv";
                break;
            case 3:
                hasLabel = true;
                edges_fname = "../dataset/Toy-Graphs/tourism.csv";
                break;
            case 4:
                edges_fname = "../dataset/Real-world Graphs/graph1/edges.csv";
                nodes_fname = "../dataset/Real-world Graphs/graph1/nodes.csv";
                break;
            case 5:
                edges_fname = "../dataset/Real-world Graphs/graph2/edges.csv";
                nodes_fname = "../dataset/Real-world Graphs/graph2/nodes.csv";
                break;
            case 6:
                edges_fname = "../dataset/Real-world Graphs/graph3/edges.csv";
                nodes_fname = "../dataset/Real-world Graphs/graph3/nodes.csv";
                break;
            case 7:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_25.csv";
                nodes_fname = "no file chosen";
                break;
            case 8:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_50.csv";
                nodes_fname = "no file chosen";
                break;
            case 9:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_75.csv";
                nodes_fname = "no file chosen";
                break;
            case 10:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_100.csv";
                nodes_fname = "no file chosen";
                break;
            case 11:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_200.csv";
                nodes_fname = "no file chosen";
                break;
            case 12:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_300.csv";
                nodes_fname = "no file chosen";
                break;
            case 13:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_400.csv";
                nodes_fname = "no file chosen";
                break;
            case 14:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_500.csv";
                nodes_fname = "no file chosen";
                break;
            case 15:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_600.csv";
                nodes_fname = "no file chosen";
                break;
            case 16:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_700.csv";
                nodes_fname = "no file chosen";
                break;
            case 17:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_800.csv";
                nodes_fname = "no file chosen";
                break;
            case 18:
                edges_fname = "../dataset/Extra_Fully_Connected_Graphs/edges_900.csv";
                nodes_fname = "no file chosen";
                break;
            case 0:
                localSession = false;
                break;
        }

    }

    std::vector<Edge> edgesVEC = Utility::loadDataFromCSV<Edge>(edges_fname,hasLabel);

    if(nodes_fname != "no file chosen"){
        std::vector<Node> nodesVEC = Utility::loadDataFromCSV<Node>(nodes_fname,hasLabel);
        for(const auto& node: nodesVEC){
            graph.addNode(node.getId());
        }
        nodesVEC.clear();
    }

    for(const auto& edge: edgesVEC){
        graph.addEdge(edge);
    }
    edgesVEC.clear();

    return true;
}





