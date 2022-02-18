//
// Created by Admin on 02.07.2021.
//

#ifndef LISTS_LIST_MANAGER_H
#define LISTS_LIST_MANAGER_H

#include "List.h"
#include "Interaction.h"
#include <iostream>
#include <vector>
#include <algorithm>

class List_Manager {
    static int current_list;
    static int first_saved_list;
    static std::vector<List>Mother;
public:
    static void fill_the_vector();
    static void pick_a_list();
    static bool validate_name(const std::string & new_name);
    static void add_new_list();
    static void rename_current_list();
    static void add_new_elements();
    static void delete_whole_list();
    static void delete_element();
    static void move_between_lists();
    static void merge_two_lists();
    static void show_list();
    static void save_all();
};

#endif //LISTS_LIST_MANAGER_H
