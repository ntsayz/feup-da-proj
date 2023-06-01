//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Menu.h"
unsigned int Menu::Main() {
    int choice;
    Utility::header("Routing Algorithm for Ocean Shipping and Urban Deliveries");
    Utility::header("Main Menu");
    Utility::body("Choose",{"1.Choose file(s) to load data from","2.Show data from current Graph(testing)"});
    Utility::footer("9.Quit");
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}


void Menu::GetCustomFiles() {
    Utility::clear_screen();
    Utility::header("Routing Algorithm for Ocean Shipping and Urban Deliveries");
    Utility::header("File names");
    Utility::body("Write the stations and network file name (in order)",{"Make sure that all files are in the src/dataset directory","","Write the names of the files for the stations(1st) and network(2nd). eg:. your_stations.csv | your_network.csv)"});
    Utility::footer();
}


unsigned int Menu::DataLoader(std::string& f1, std::string& f2) {
    int choice;
    Utility::header("Routing Algorithm for Ocean Shipping and Urban Deliveries");
    Utility::header("Import data from files");
    Utility::body("Path of files to import data from at the moment",{"Nodes- "+ f1,"Edges- "+ f2,""});
    Utility::body("Choose from which files would you like to import the data from:",
                  {
                          "Toy Graphs",
                          "-----------",
                          "1.Shipping",
                          "2.Stadiums",
                          "3.Tourism",
                          "",
                          "Real Graphs",
                          "-----------",
                          "4. Graph 1",
                          "5. Graph 2",
                          "6. Graph 3",
                          "",
                          "Fully Connected Graphs",
                          "----------------------",
                          "7. 25 Nodes",
                          "8. 50 Nodes",
                          "9. 75 Nodes",
                          "10. 100 Nodes",
                          "11. 200 Nodes",
                          "12. 300 Nodes",
                          "13. 400 Nodes",
                          "14. 500 Nodes",
                          "15. 600 Nodes",
                          "16. 700 Nodes",
                          "17. 800 Nodes",
                          "18. 900 Nodes"
                  });

    Utility::footer("0.Continue");
    std::cin >> choice;
    Utility::clear_screen();
    if(choice == 0)return 0;
    return Utility::getInput(choice,1,18);
}



