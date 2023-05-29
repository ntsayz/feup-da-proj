//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Menu.h"
unsigned int Menu::Main() {
    int choice;
    Utility::header("Graphs");
    Utility::header("Main Menu");
    Utility::body("Choose",{"1.TBD","2.Feature #2"});
    Utility::footer("9.Quit");
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}

unsigned int Menu::DataLoader(std::string& f1, std::string& f2) {
    int choice;
    Utility::header("Graphs");
    Utility::header("Import data from files");
    Utility::body("Path of files to import data from at the moment",{f1,f2,""});
    Utility::body("Choose from which files would you like to import the data from:"
            ,{"Toy Graphs"
      ,"1.Shipping","2.Stadiums","3.Tourism","Real Graphs","4. Graph 1","5. Graph 2","6. Graph 3"});
    Utility::footer("9.Continue");
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,6);
}

void Menu::GetCustomFiles() {
    Utility::clear_screen();
    Utility::header("Graphs");
    Utility::header("File names");
    Utility::body("Write the stations and network file name (in order)",{"Make sure that all files are in the src/dataset directory","","Write the names of the files for the stations(1st) and network(2nd). eg:. your_stations.csv | your_network.csv)"});
    Utility::footer();
}




