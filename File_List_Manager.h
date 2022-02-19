//
// Created by Jan on 15.02.2022.
//

#ifndef LISTS_FILE_LIST_MANAGER_H
#define LISTS_FILE_LIST_MANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "List.h"
#include "Product.h"

class File_List_Manager {
    static std::vector<std::string> Saved_Lists_Register;
public:
    static void fill_register();
    static void save_list_to_file(const std::string & list_name);
    static List read_list_from_file(const std::string & list_name);
};


#endif //LISTS_FILE_LIST_MANAGER_H
