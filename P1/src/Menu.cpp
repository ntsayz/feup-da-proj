//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Menu.h"
int Menu::Main() {
    int choice;
    Utility::header("Portugal Railway");
    Utility::header("Main Menu");
    Utility::body("Choose",{"1.idk"});
    Utility::footer();
    std::cin >> choice;
    Utility::clear_screen();
    return Utility::getInput(choice,1,2);
}