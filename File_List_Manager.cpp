//
// Created by Jan on 15.02.2022.
//

#include "File_List_Manager.h"

std::vector<std::string> File_List_Manager::Saved_Lists_Register;
/*
void File_List_Manager::fill_register() {
    std::fstream file_holder("register.txt");
    std::string element;
    if(file_holder) {
        while(std::getline(file_holder, element)) {
            Saved_Lists_Register.push_back(element);
        }
        file_holder.close();
    }
    else {
        std::cout << "Bad file\n";
    }
}

void File_List_Manager::save_list_to_file(const std::string &list_name) {
    try {
        //todo dawać sprawdzenie czy pusta lista
        std::fstream file_holder;
            file_holder.open(this->name + ".txt", std::ios::out);
            if(!file_holder)
                std::cout << "Bad file!";
            else {
                std::shared_ptr<Product> Temp = first;
                while(Temp) {
                    file_holder << Temp->get_name() << " " << Temp->get_quantity() << "\n";
                    Temp=Temp->next;
                }
                file_holder.close();
            }
    }
    catch(const Invalid_List & invalid_list) {}
}

List File_List_Manager::read_list_from_file(const std::string &list_name) {
    std::fstream file_holder(list_name));
    if(!file_holder)
        std::cout << "Bad file!\n";
    else {
        while(std::getline)
    }
}
*/