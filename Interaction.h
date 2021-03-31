//
// Created by Admin on 17.03.2021.
//

#ifndef LISTS_INTERACTION_H
#define LISTS_INTERACTION_H

#include <exception>

struct Bad_Input : public std::exception{
    std::string message;
    const char * what() const noexcept override{
        return message.c_str();
    }
    explicit Bad_Input(std::string msg = "Wrong input! You are out of range! Type it once more") : message(std::move(msg)){};
};

class Interaction {
public:
    static int simply_get_int();
    static int get_choice(int left_lim, int right_lim);
    static std::string get_str();
    static bool sure();
};


#endif //LISTS_INTERACTION_H
