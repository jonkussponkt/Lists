//
// Created by Admin on 17.03.2021.
//

#include <iostream>
#include <string>
#include "Interaction.h"

int Interaction::simply_get_int() {
    int number;
    std::string str = get_str();
    for(auto & i : str) {
        if (!isdigit(i))
            throw Bad_Input("Input a number!!!\n");
    }
    number = std::stoi(str);
    if(number < 1)
        throw Bad_Input();
    return number;
}

int Interaction::get_choice(int left_lim, int right_lim) {
    int choice;
    std::string str = get_str();
    for(auto & i : str){
        if(!isdigit(i))
            throw Bad_Input("Input a number!!!\n");
    }
    choice = std::stoi(str);
    if(choice < left_lim || choice > right_lim){
        throw Bad_Input();
    }
    return choice;
}

bool Interaction::sure() {
    std::cout << "Are you sure? If so press 1, otherwise press anything\n";
    std::string str = get_str();
    return str == "1";
}

std::string Interaction::get_str() {
    std::string str;
    getline(std::cin, str);
    return str;
}
