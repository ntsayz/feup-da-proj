//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Menu.h"
unsigned int Menu::Main() {
    int choice;
    Utility::header("Portugal Railway");
    Utility::header("Main Menu");
    Utility::body("Choose",{"1.idk"});
    Utility::footer();
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}

unsigned int Menu::DataLoader(std::string& f1, std::string& f2) {
    int choice;
    Utility::header("Portugal Railway");
    Utility::header("Import data from files");
    Utility::body("Path of files to import data from at the moment",{f1,f2,""});
    Utility::body("Choose from which files would you like to import the data from:"
            ,{"1. Default (Given in the dataset)"
      ,"2. Custom"});
    Utility::footer();
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}

void Menu::GetCustomFiles() {
    Utility::clear_screen();
    Utility::header("Portugal Railway");
    Utility::header("File names");
    Utility::body("Write the stations and network file name (in order)",{"Make sure that all files are in the src/dataset directory","","Write the names of the files for the stations(1st) and network(2nd). eg:. your_stations.csv | your_network.csv)"});
    Utility::footer();
}




