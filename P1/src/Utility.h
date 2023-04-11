//
// Created by Ntsay Zacarias on 07/03/2023.
//

#ifndef SRC_UTILITY_H
#define SRC_UTILITY_H
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Menu.h"
/**
    @class Utility
    @brief Seeing that a lot of functionality is used very often, to avoid repeated code we created a helper class that encapsulated and made our easier throughout the development of this application
*/

class Utility {
private:
    static const int LENGTH = 150;
public:
    /// Auxiliary function, to get a number from user input given a range
    /// \param choice
    /// \param min
    /// \param max
    /// \return
    static int getInput(int choice, int min, int max);
    /// Auxiliary function, to get a number from user input
    /// \param code
    /// \return
    static int getCode(int code);
    /**
	* @brief Clear screen (Cross-Platform)
	*/
    static void clear_screen();
    /**
	* @brief Auxiliary function, to print the menu's footer
	*/
    static void footer();
    /**
	* @brief Auxiliary function, to print the menu's header
	*/
    static void header(const std::string& title);
    /**
	* @brief Auxiliary function, to print the menu's body
	*/
    static void body(const std::string& description, std::vector<std::string> options);
    /// Checks if a string is contained in another
    /// \param str String to check
    /// \param sub Substring
    /// \return
    static bool isSubstring(std::string str, std::string sub);
    /// Gets file names from user
    /// \param str String to check
    /// \param sub Substring
    /// \return
    static void get_filenames(std::string& f1,std::string& f2);
    /// Loads data from the .csv files
    /// \tparam T Guarantees that any datatype can be used
    /// \param filename
    /// \return
    template <typename T>
    static std::vector<T> loadDataFromCSV(std::string filename) {
        std::vector<T> data;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return data;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            T object = T::fromCSVLine(iss);
            data.push_back(object);
        }

        return data;
    }

    static void footer(std::string text);

    static void get_string(std::string &f1);

    static std::string getName(std::string purpose);

    static double getDoubleInput(double min, double max);
};


#endif //SRC_UTILITY_H
