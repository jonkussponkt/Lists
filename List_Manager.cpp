//
// Created by Admin on 02.07.2021.
//

#include "List_Manager.h"

int List_Manager::current_list = -1;
std::vector<List> List_Manager::Mother;

void List_Manager::fill_the_vector() {
    std::vector<std::string> files;
    std::fstream file_holder("register.txt");
    List Temp_List;
    if(!file_holder)
        std::cout << "Bad file!";
    else {
        if(file_holder) {
            std::string element;
            int lines = 0;
            while(std::getline(file_holder, element)) {
                files.push_back(element);
                if(lines == 0 && element.empty())
                    break;
                lines++;
            }
            file_holder.close();
            if(lines > 0) {
                for (auto &i: files) {
                    Temp_List = List(i);
                    Temp_List.read_list(i);
                    Mother.push_back(Temp_List);
                }
            }
        }
        else {
            std::cout << "Bad\n";
        }
    }
}

void List_Manager::pick_a_list() {
    int ID = 1, chosen_list = -1;
    std::string element;
    if(Mother.empty())
        throw Invalid_List("You have not created any list. Choose once more.");
    else if(Mother.size() == 1)
        current_list = 1;
    else {
        try {
            do {
                for(auto & i : Mother) {
                    std::cout << ID << " " << i.get_name() << std::endl;
                    ID++;
                }

                std::cout << "Pick ID number of list:\n";
                chosen_list = Interaction::get_choice(1, Mother.size());
            }
            while(chosen_list < 1 || chosen_list > Mother.size());
        }
        catch (const Bad_Input & bad_input){
            std::cout << bad_input.what();
        }
        catch (const std::invalid_argument & inv_arg){
            std::cout << "Pick a number!!!!\n";
        }
//        if(ID >= Mother.size()) {
//            std::string new_name = File_Mother[ID - Mother.size() - 1];
//            List Temp_List = List(new_name);
//            Temp_List.read_list(new_name);
//            Mother.push_back(Temp_List);
//        }
        current_list = chosen_list;
    }
}

bool List_Manager::validate_name(const std::string &new_name) {
    for(auto & i : Mother)
        if(i.get_name() == new_name)
            return false;
    return true;
}

void List_Manager::add_new_list() {
    std::string name;
    if(current_list > 0)
        std::cout << "YOUR CURRENT LIST IS NR " << current_list << " " << Mother[current_list - 1].get_name() << std::endl;
    else
        std::cout << "You have not created any list\n";
    if(Mother.size() < 10) {
        std::cout << "Input name of the list\n";
        while (name.empty() && !validate_name(name)) {
            try {
                name = Interaction::get_str();
            }
            catch (const Bad_Input &bad_input) {
                std::cout << bad_input.what();
            }
        }
        List Temp_List = List(name);
        Mother.push_back(Temp_List);
        current_list = Mother.size();
        name.clear();
    }
    else
        std::cout << "You cannot have more than 10 lists! Delete anything\n";
}

void List_Manager::rename_current_list() {
    std::string name;
    if(Mother.empty())
        std::cout << "You have not created any list. Choose once more.\n";
    else {
        std::cout << "Input new name of the list (must not be empty)\n";
        while(name.empty()) {
            try {
                name = Interaction::get_str();
            }
            catch(const Bad_Input & bad_input) {
                std::cout << bad_input.what();
            }
        }
        Mother[current_list - 1].set_name(name);
        name.clear();
    }
}

void List_Manager::add_new_elements() {
    int list_size, new_elements = -1, element;
    std::string name;
    if(current_list > 0) {
        list_size = Mother[current_list - 1].get_size();
        std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
        do {
            try {
                if(!Mother[current_list - 1].full_list()) {
                    std::cout << "How many elements (1-" << 10 - list_size
                              << ") do you want to add to the list nr " << current_list << "\n";
                    std::cout << "To go back to the main menu press 0\n";
                    new_elements = Interaction::get_choice(0, 10 - list_size);
                }
            }
            catch (const Bad_Input &bad_input) {
                std::cout << bad_input.what();
            }
            catch (const std::invalid_argument &inv_arg) {
                std::cout << "Pick a number!!!!\n";
            }
        }
        while (new_elements < 0 || new_elements > 10 - list_size);

        element = 1;
        if(new_elements > 0) {
            while (element <= new_elements) {
                std::cout << Mother[current_list - 1];
                std::cout << "Input name of product nr " << element << " \n";
                std::cout << "Press enter to come back to main menu\n";
                try {
                    name = Interaction::get_str();
                }
                catch (const Bad_Input & bad_input) {}

                if (!name.empty()) {

                    int first_number = -1;
                    std::string unit;
                    do {
                        try {
                            std::cout << "Input quantity\n";
                            first_number = Interaction::simply_get_int();
                            std::cout << "Input unit if necessary, otherwise press enter\n";
                            try {
                                unit = Interaction::get_str();
                            }
                            catch (const Bad_Input &bad_input) {};
                        }
                        catch (const Bad_Input &bad_input) {
                            std::cout << bad_input.what();
                        }
                        catch (const std::invalid_argument &inv_arg) {
                            std::cout << "Pick a number!!!!\n";
                        }
                    } while (first_number < 1);

                    //  todo nie dziala wyswietlanie jednostek

                    Product Temp = Product(name, unit, first_number);

                    if (list_size == 0) {
                        Mother[current_list - 1].add_new_element(Temp, 1);
                        list_size++;
                        element++;
                    } else {
                        int pos;
                        pos = Mother[current_list - 1].is_in_the_list(Temp.name);
                        if (pos == -1) {
                            do {
                                try {
                                    pos = -1;
                                    std::cout << "Input position of the element in the list (1-"
                                              << list_size + 1
                                              << ")\nTo set product at the end of the list press "
                                              << list_size + 1
                                              << std::endl;
                                    pos = Interaction::get_choice(1, list_size + 1);
                                    Mother[current_list - 1].add_new_element(Temp, pos);
                                    list_size++;
                                    element++;
                                }
                                catch (const Bad_Input &bad_input) {
                                    std::cout << bad_input.what();
                                }
                                catch (const std::invalid_argument &inv_arg) {
                                    std::cout << "Pick a number!!!!\n";
                                }
                            } while (pos < 1 || pos > list_size);
                        } else {
                            std::cout
                                    << "You've already put this item on the list. Do you want to sum it with quantity of ";
                            std::cout << Temp.get_name() << " (" << Mother[current_list - 1][pos]->get_quantity()
                                      << ")?\n"; /// wyświetla ilośc produktu
                            if (Interaction::sure()) {
                                Mother[current_list - 1][pos]->set_quantity(
                                        Mother[current_list - 1][pos]->get_quantity() + first_number);
                                element++;
                            }
                        }
                    }
                }
                name.clear();
            }
        }
    }
    else
        std::cout << "You have not created any list\n";
}

void List_Manager::delete_whole_list() {
    int list_size, first_list = -1;
    list_size = Mother.size();
    if(list_size == 0)
        std::cout << "You have not created any lists\n";
    else if(list_size == 1)
        first_list = 1;
    else {
        do {
            try {
                std::cout << "Input number of list you want to remove\n";
                if (list_size < 2) {
                    first_list = Interaction::simply_get_int();
                    list_size = 2;
                }
                else
                    first_list = Interaction::get_choice(1, list_size);
            }
            catch (const Bad_Input &bad_input) {
                std::cout << bad_input.what();
            }
            catch (const std::invalid_argument &inv_arg) {
                std::cout << "Pick a number!!!!\n";
            }
        }
        while (first_list < 1 && first_list > list_size);
    }
    if(list_size > 0 && Interaction::sure()) {
        Mother.erase(Mother.begin() + first_list - 1);
        if (first_list == current_list)
            current_list = -1;
    }
}

void List_Manager::delete_element() {
    int first_list = -1, list_size, first_number = -1;
    if(Mother.size() > 0) {
        first_list = current_list;
        list_size = Mother[first_list - 1].get_size();
        std::cout << Mother[first_list - 1];

        if (list_size == 0) {
            throw Invalid_List("The list is empty\n");
        }
        else if (list_size == 1)
            first_list = 1;
        else {
            do {
                try {
                    if (current_list > 0)
                        std::cout << "YOUR CURRENT LIST IS NR " << current_list << " " << Mother[current_list - 1].get_name() << std::endl;
                    std::cout << "Input position of element you want to remove\n";
                    first_number = Interaction::get_choice(1, list_size);
                }
                catch (const Bad_Input &bad_input) {
                    std::cout << bad_input.what();
                }
                catch (const std::invalid_argument &inv_arg) {
                    std::cout << "Pick a number!!!!\n";
                }
            } while (first_number < 1 || first_number > list_size+1);
        }
        if (Interaction::sure()) {
            Mother[first_list - 1].remove_from_the_list(first_number);
            std::cout << "The product was successfully removed\n";
        }
    }
    else
        std::cout << "You have not created any list\n";
}


void List_Manager::move_between_lists() {
    if(Mother.size() < 2) {
        std::cout << "To move products between lists you have to create at least two lists\n";
    }
    else {
        int first_list = -1, first_number = -1, second_list = -1, second_number = -1;
        first_list = current_list;
        int list_size = Mother[first_list - 1].get_size();

        if (list_size < 1) {
            throw Invalid_List("The list is empty\n");
        }
        else {
            do {
                try {
                    if (current_list > 0) {
                        std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                        std::cout << Mother[current_list - 1];
                    }
                    std::cout << "Input number of product\n";
                    first_number = Interaction::get_choice(1, list_size);
                }
                catch (const Bad_Input &bad_input) {
                    std::cout << bad_input.what();
                }
                catch (const std::invalid_argument &inv_arg) {
                    std::cout << "Pick a number!!!!\n";
                }
            }
            while (first_number < 1 || first_number > list_size);

            Product Temp = *Mother[first_list - 1][first_number - 1];

            int mother_size = Mother.size();
            if (mother_size < 2) {
                throw std::range_error("You have not created at least 2 lists\n");
            }
            do {
                try {
                    std::cout << "Input number of list where you want to move product:\n";
                    second_list = Interaction::get_choice(1, mother_size);
                }
                catch (const Bad_Input &bad_input) {
                    std::cout << bad_input.what();
                }
                catch (const std::invalid_argument &inv_arg) {
                    std::cout << "Pick a number!!!!\n";
                }
            }
            while (second_list < 1 || second_list > mother_size || second_list == first_list);

            list_size = Mother[second_list - 1].get_size();
            int current_position = Mother[second_list - 1].is_in_the_list(Temp.get_name());

            if(current_position == -1) {
                if (list_size == 0)
                    second_number = 1;
                else if (list_size == 1)
                    second_number = 2;
                do {
                    try {
                        std::cout << "Input position of the product on the list nr " << second_list;
                        std::cout << std::endl << Mother[second_list - 1];
                        second_number = Interaction::get_choice(1, list_size + 1);
                    }
                    catch (const Bad_Input &bad_input) {
                        std::cout << bad_input.what();
                    }
                    catch (const std::invalid_argument &inv_arg) {
                        std::cout << "Pick a number!!!!\n";
                    }
                }
                while (second_number < 1 || second_number > list_size+1);
            }

            if(Interaction::sure()) {
                if(current_position > -1)
                    Mother[second_list - 1][current_position]->set_quantity(Mother[second_list - 1][current_position]->get_quantity()+Temp.get_quantity());
                else
                    Mother[second_list - 1].add_new_element(Temp, second_number);
                Mother[first_list - 1].remove_from_the_list(first_number);
                std::cout << "The product was successfully moved\n";
            }
        }
    }
}

void List_Manager::merge_two_lists() {
    int mother_size = Mother.size();
    int first_list, second_list = -1;
    if(mother_size < 2) {
        throw std::range_error("To merge lists you have to create at least two lists\n");
    }
    do {
        try {
            first_list = -1;
            std::cout << "Input number of first list\n";
            first_list = Interaction::get_choice(1, mother_size);
        }
        catch (const Bad_Input & bad_input){
            std::cout << bad_input.what();
        }
        catch (const std::invalid_argument & inv_arg){
            std::cout << "Pick a number!!!!\n";
        }
    }
    while(first_list < 1 || first_list > mother_size);

    do {
        mother_size = Mother.size();
        try {
            std::cout << "Input number of second list\n";
            second_list = Interaction::get_choice(1, mother_size);
        }
        catch (const Bad_Input & bad_input){
            std::cout << bad_input.what();
        }
        catch (const std::invalid_argument & inv_arg){
            std::cout << "Pick a number!!!!\n";
        }
    }
    while(second_list < 1 || second_list > mother_size || second_list == first_list);

    try {
        if (Mother[first_list - 1].not_empty_list() && Mother[second_list - 1].not_empty_list()) {
            if (Interaction::sure()) {
                Mother[first_list - 1].merge_lists(Mother[second_list - 1]);
                Mother.erase(Mother.begin() + second_list - 1);
            }
        }
        current_list = 1;
    }
    catch(const Invalid_List & invalid_list) {
        std::cout << invalid_list.what();
    }
}

void List_Manager::show_list() {
    int mother_size = Mother.size();
    int first_list = -1;
    if(mother_size == 0) {
        throw std::range_error("You have not created any lists\n");
    }
    else if(mother_size == 1)
        first_list = 1;
    else {
        do {
            try {
                std::cout << "Input number of list:\n";
                for(int i = 0; i < mother_size; i++)
                    std::cout << i + 1 << " " << Mother.at(i).get_name() << std::endl;
                first_list = Interaction::get_choice(1, mother_size);
            }
            catch (const Bad_Input &bad_input) {
                std::cout << bad_input.what();
            }
            catch (const std::invalid_argument &inv_arg) {
                std::cout << "Pick a number!!!!\n";
            }
        }
        while (first_list < 1 || first_list > mother_size);
    }
    std::cout << Mother[first_list - 1];
}

void List_Manager::save_all() {
    for (auto & i: Mother)
        i.save_list();
}
