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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }else if (choice < min || choice > max) {
            return -1;
        }

        return choice;
    }
}

void Utility::clear_screen() {
    std::system("clear");
}
void Utility::header(const std::string& title){
    int n = (int)(title.size() + 59) / 2;
    std::cout << "|" << std::setfill('-') <<std::setw(59) << "|\n"; // ---
    std::cout << "|" << std::setfill(' ') << std::setw(n); // | txt
    std::cout << title;
    std::cout << std::setfill(' ') <<std::setw(59 -n)<<"|\n"  //  --> |
              << "|"<< std::setfill('-') <<std::setw(59) <<"|\n";
}

void Utility::footer() {
    std::cout << "|" << std::setfill('-') <<std::setw(59) << "|\n"; // --
    std::cout << "|" << std::setfill(' ')<< std::setw(33) << "9.Back  " << std::setw(26) << "|\n";
    std::cout << "|" << std::setfill('-') <<std::setw(59) << "|\n";
    std::cout << "-->";
}

void Utility::body(const std::string& description, std::vector<std::string> options){
    int n = (int)(description.size() + 59) / 2;
    std::cout << "|" << std::setfill(' ') << std::setw(n) << description;
    std::cout << std::setfill(' ') <<std::setw(59- n)<<"|\n";
    std::cout << "|" << std::setfill(' ') <<std::setw(59) << "|\n";
    for(int i =0; i < options.size(); i++){
        int k = (int)(options[i].size() + 59) / 2;
        std::cout << "|" << std::setfill(' ') << std::setw(k) << options[i] << std::setw(59 - k) << "|\n";
    }

}

bool Utility::isSubstring(std::string str, std::string sub)
{
    return str.find(sub) != std::string::npos;
}

