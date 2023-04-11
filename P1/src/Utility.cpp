//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Utility.h"


int  Utility::getInput(int choice, int min, int max)  {
    while(true){
        if(choice == 9) return choice;
        if (std::cin.fail()) {
            std::cerr << "Sorry, I cannot read that. Please try again." << std::endl;
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }else if (choice < min || choice > max) {
            return -1;
        }

        return choice;
    }
}
double Utility::getDoubleInput(double min, double max) {
    double choice;

    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cerr << "Sorry, I cannot read that. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if (choice < min || choice > max) {
            std::cerr << "Please enter a value between " << min << " and " << max << "." << std::endl;
            continue;
        }

        return choice;
    }
}


void Utility::clear_screen() {
    std::system("clear");
}
void Utility::header(const std::string& title){
    int n = (int)(title.size() + LENGTH) / 2;
    std::cout << "|" << std::setfill('-') <<std::setw(LENGTH) << "|\n"; // ---
    std::cout << "|" << std::setfill(' ') << std::setw(n); // | txt
    std::cout << title;
    std::cout << std::setfill(' ') <<std::setw(LENGTH -n)<<"|\n"  //  --> |
              << "|"<< std::setfill('-') <<std::setw(LENGTH) <<"|\n";
}

void Utility::footer() {
    std::cout << "|" << std::setfill('-') <<std::setw(LENGTH) << "|\n"; // --
    std::cout << "|" << std::setfill(' ')<< std::setw((LENGTH/2)+3) << "9.Back" << std::setw((LENGTH/2)-3) << "|\n";
    std::cout << "|" << std::setfill('-') <<std::setw(LENGTH) << "|\n";
    std::cout << "-->";
}
void Utility::footer(std::string text) {
    std::cout << "|" << std::setfill('-') <<std::setw(LENGTH) << "|\n"; // --
    std::cout << "|" << std::setfill(' ')<< std::setw((LENGTH/2)+(int)(text.size()/2)) << text << std::setw((LENGTH/2)-(int)(text.size()/2)) << "|\n";
    std::cout << "|" << std::setfill('-') <<std::setw(LENGTH) << "|\n";
    std::cout << "-->";
}

void Utility::body(const std::string& description, std::vector<std::string> options){
    int n = (int)(description.size() +LENGTH ) / 2;
    std::cout << "|" << std::setfill(' ') << std::setw(n) << description;
    std::cout << std::setfill(' ') <<std::setw(LENGTH- n)<<"|\n";
    std::cout << "|" << std::setfill(' ') <<std::setw(LENGTH) << "|\n";
    for(int i =0; i < options.size(); i++){
        int k = (int)(options[i].size() + LENGTH) / 2;
        std::cout << "|" << std::setfill(' ') << std::setw(k) << options[i] << std::setw(LENGTH - k) << "|\n";
    }

}

bool Utility::isSubstring(std::string str, std::string sub)
{
    return str.find(sub) != std::string::npos;
}

void Utility::get_filenames(std::string& f1, std::string& f2) {
    std::regex pattern("\\.csv$");
    while (true){
        Menu::GetCustomFiles();
        std::getline(std::cin,f1);
        std::cout << "-->";
        std::getline(std::cin,f2);
        if(f1.empty() || f2.empty()){
            continue;
        }else if(f1 == "9" || f2 == "9"){
            return;
        }else if(!(std::regex_search(f1, pattern) && std::regex_search(f2, pattern))){
            std::cerr << "The file name has to finish with .csv";
            continue;
        }else{
            f1.insert(0,"../dataset/");
            f2.insert(0,"../dataset/");
            return;
        }
    }
}

void Utility::get_string(std::string& f1) {
    while (true){
        std::getline(std::cin,f1);


        if(f1.empty() ){
            continue;
        }else if(f1 == "9"){
            return;
        }
    }
}

std::string Utility::getName(std::string purpose){
    std::string stringin;
    while (true){
        Utility::clear_screen();
        Utility::header("PR");
        Utility::body("Write the name of the",{purpose});
        Utility::footer();
        std::getline(std::cin,stringin);
        if(stringin.empty()){
            continue;
        }else if(stringin == "9" || stringin == "exit"){
            return "exit";
        }else if(stringin.size() < 2){
            std::cerr << "A bit longer please!";
            continue;
        }else{
            return stringin;
        }
    }

}
