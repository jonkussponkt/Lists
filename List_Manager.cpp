//
// Created by Admin on 02.07.2021.
//

#include "List_Manager.h"

int List_Manager::current_list = -1;   ///initialization of static members of class List_Manager
std::vector<std::string> List_Manager::files;
std::vector<List> List_Manager::Mother;

void List_Manager::fill_the_vector() {
    std::fstream file_holder("register.txt");     ///register.txt is a file that includes names of lists saved in previous sessions
    List Temp_List;
    if(!file_holder)
        std::cout << "Bad file!";
    else {
        if(file_holder) {
            std::string element;
            int lines = 0;
            while(std::getline(file_holder, element)) {  ///reading file line by line
                files.push_back(element);
                if(lines == 0 && element.empty())       ///if no lists were created
                    break;
                lines++;
            }
            file_holder.close();
            if(lines > 0) {
                for (auto &i: files) {
                    Temp_List = List(i);
                    Temp_List.read_list(i);    ///creating new list based on information from file
                    Mother.push_back(Temp_List);
                }
                current_list = 1;                      ///first list is set as current list
            }
        }
    }
}

void List_Manager::pick_a_list() {
    int ID = 1, chosen_list = -1;
    std::string element;
    if(Mother.empty())
        throw Invalid_List("You have not created any list. Choose once more.\n");
    else if(Mother.size() == 1) {               ///if only one list was created
        current_list = 1;
        std::cout << "You have created one list - " << Mother[0].get_name() << std::endl;
    }
    else {
        try {
            do {
                for(auto & i : Mother) {       ///writing names of all lists
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
        current_list = chosen_list;
    }
}

bool List_Manager::validate_name(const std::string &new_name) { ///checks if any list was previously named like new_name
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
    std::cout << "Input name of the list\n"
                 "To go back to the main menu press 0\n";
    bool correct_name = false;
    if(Mother.size() < 15) {     ///max amount of lists is 15
        while (name.empty() || !correct_name) {        ///name cannot be empty and name must be unique
            try {
                if(!name.empty() && !correct_name)
                    std::cout << "The name " << name << " has been used before. Input different name\n";
                name = Interaction::get_str();
                correct_name = validate_name(name); ///name validation, name of each list must be unique
            }
            catch (const Bad_Input &bad_input) {
                std::cout << bad_input.what();
            }
        }
        if(name != "0") {                                   ///0 means that user wants to leave the process of adding list
            List Temp_List = List(name);
            Mother.push_back(Temp_List);
            current_list = Mother.size();
        }
        name.clear();
    }
    else
        std::cout << "You cannot have more than 15 lists! To add a new one delete \n";
}

void List_Manager::rename_current_list() {
    std::string name;
    if(Mother.empty())              ///cannot rename anything if there is no list in vector :)
        std::cout << "You have not created any list. Choose once more.\n";
    else if(current_list <= 0)
        std::cout << "You have not picked current list\n";
    else {
        std::cout << "Input new name of the list (must not be empty)\n"
                     "To go back to the main menu press 0\n";
        while(name.empty()) {
            try {
                name = Interaction::get_str();
            }
            catch(const Bad_Input & bad_input) {
                std::cout << bad_input.what();
            }
        }
        if(name != "0")              ///0 means that user wants to leave the process of adding list
            Mother[current_list - 1].set_name(name);
        name.clear();
    }
}

void List_Manager::add_new_elements() {
    int list_size, new_elements = -1, element;
    std::string name;
    if(current_list > 0 && !Mother[current_list - 1].full_list()) {    ///cannot add to current list if there is no current lust and if current list is full
        list_size = Mother[current_list - 1].get_size();
        std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
        do {
            try {
                if(!Mother[current_list - 1].full_list()) {            ///cannot add new elements to full list
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
        while (new_elements < 0 || new_elements > 10 - list_size);    ///max 10 elements on each list

        element = 1;
        if(new_elements > 0) {
            while (element <= new_elements) {
                std::cout << Mother[current_list - 1];
                std::cout << "Input name of product nr " << element << " \n";
                std::cout << "Press enter to come back to main menu\n";
                try {
                    name = Interaction::get_str();
                    if (!name.empty()) {        ///product name cannot be empty
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

                        if (list_size == 0) {   ///if list is empty it is not necessary to check if there are duplicates in the list
                            Mother[current_list - 1].add_new_element(Temp, 1);
                            list_size++;
                            element++;
                        } else {
                            int pos;
                            pos = Mother[current_list - 1].is_in_the_list(Temp.name); ///checks if product is in the list, then checks position of the product in the list
                            if (pos == -1) {  ///if product is not in the list
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
                            } else { /// if product is in the list
                                std::cout
                                        << "You've already put this item on the list. Do you want to sum it with quantity of ";
                                std::cout << Temp.get_name() << " (" << Mother[current_list - 1][pos]->get_quantity()
                                          << ")?\n"; ///
                                if (Interaction::sure()) { /// sums new quantity with old quantity
                                    Mother[current_list - 1][pos]->set_quantity(
                                            Mother[current_list - 1][pos]->get_quantity() + first_number);
                                    element++;
                                }
                            }
                        }
                    }
                }
                catch (const Bad_Input & bad_input) {
                    element = new_elements + 1; ///to leave the loop (line 159)
                }
                name.clear();
            }
        }
    }
    else if(Mother[current_list - 1].full_list())
        std::cout << "The list is full\n";
    else
        std::cout << "You have not created any list\n";
}

void List_Manager::delete_whole_list() {
    int list_size, first_list = -1;
    list_size = Mother.size();
    if(list_size == 0)      /// if there are no lists nothing cannot be deleted :)
        std::cout << "You have not created any lists\n";
    else if(list_size == 1) /// if there is one list only one list can be deleted
        first_list = 1;
    else {    /// if there is more than 1 list user can choose list to delete
        do {
            try {
                std::cout << "Input number of list you want to remove\n"
                             "To go back to the main menu press 0\n";
                for(int i = 0; i < list_size; i++)
                    std::cout << i + 1 << " " << Mother.at(i).get_name() << std::endl;
                if (list_size < 2) {
                    first_list = Interaction::simply_get_int();
                    list_size = 2;
                }
                else
                    first_list = Interaction::get_choice(0, list_size);
            }
            catch (const Bad_Input &bad_input) {
                std::cout << bad_input.what();
            }
            catch (const std::invalid_argument &inv_arg) {
                std::cout << "Pick a number!!!!\n";
            }
        }
        while (first_list < 0 && first_list > list_size);
    }
    if(list_size > 0 && Interaction::sure()) {
        Mother.erase(Mother.begin() + first_list - 1);  /// erasing list of chosen index from the vector
        if (first_list == current_list)
            current_list = -1;          /// there is no current list if the only one list is deleted
    }
}

void List_Manager::delete_element() {
    int first_list, list_size, first_number = -1;
    if(Mother.size() > 0) {             /// vector must not be empty
        first_list = current_list;
        list_size = Mother[first_list - 1].get_size();
        std::cout << Mother[first_list - 1];

        if (list_size == 0)             /// nothing can be deleted when there is no list
            throw Invalid_List("The list is empty\n");
        else if (list_size == 1)        /// if there is only one list, elements can be deleted only from this one list
            first_list = 1;
        else {
            do {
                try {
                    if (current_list > 0)
                       std::cout << "YOUR CURRENT LIST IS NR " << current_list << " " << Mother[current_list - 1].get_name() << std::endl;
                    std::cout << "Input position of element you want to remove\n"
                                 "To go back to the main menu press 0\n";
                    first_number = Interaction::get_choice(0, list_size);
                }
                catch (const Bad_Input &bad_input) {
                    std::cout << bad_input.what();
                }
                catch (const std::invalid_argument &inv_arg) {
                    std::cout << "Pick a number!!!!\n";
                }
            } while (first_number < 0 || first_number > list_size+1);
        }
        if (first_number > 0) {
            if (Interaction::sure()) {      /// if user is sure element is deleted from the list
                Mother[first_list - 1].remove_from_the_list(first_number);
                std::cout << "The product was successfully removed\n";
            }
        }
    }
    else
        std::cout << "You have not created any list\n";
}


void List_Manager::move_between_lists() {
    if(Mother.size() < 2)  /// checks as message below specifies
        std::cout << "To move products between lists you have to create at least two lists\n";
    else {
        int first_list = current_list, first_number = -1, second_list = -1, second_number = -1;
        int list_size = Mother[first_list - 1].get_size();

        if (list_size < 1)      /// nothing cannot be moved from / to an empty list
            throw Invalid_List("The list is empty\n");
        else {
            do {
                try {
                    if (current_list > 0) {     /// current list is presented
                        std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                        std::cout << Mother[current_list - 1];
                    }
                    std::cout << "Input number of product\n"
                                 "To go back to the main menu press 0\n";
                    first_number = Interaction::get_choice(0, list_size);
                }
                catch (const Bad_Input &bad_input) {
                    std::cout << bad_input.what();
                }
                catch (const std::invalid_argument &inv_arg) {
                    std::cout << "Pick a number!!!!\n";
                }
            } while (first_number < 0 || first_number > list_size);

            if (first_number > 0) {
                Product Temp = *Mother[first_list - 1][first_number - 1]; /// extracting element of vector - pointer to Product object

                int mother_size = Mother.size();
                if (mother_size < 2)
                    throw std::range_error("You have not created at least 2 lists\n");
                do {
                    try {
                        std::cout << "Input number of list where you want to move product:\n";
                        for (int i = 0; i < mother_size; i++)
                            std::cout << i + 1 << " " << Mother.at(i).get_name() << std::endl;
                        second_list = Interaction::get_choice(1, mother_size);
                    }
                    catch (const Bad_Input &bad_input) {
                        std::cout << bad_input.what();
                    }
                    catch (const std::invalid_argument &inv_arg) {
                        std::cout << "Pick a number!!!!\n";
                    }
                } while (second_list < 1 || second_list > mother_size || second_list == first_list);

                list_size = Mother[second_list - 1].get_size();
                int current_position = Mother[second_list - 1].is_in_the_list(Temp.get_name()); /// checking if product is in the list

                if (current_position == -1) { /// if product is not in the second list then we get position on this list
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
                    } while (second_number < 1 || second_number > list_size + 1);
                }

                if (Interaction::sure()) {
                    if (current_position > -1) /// if element exists in the list then we simply add quantity of new object and object on the list with the same name
                        Mother[second_list - 1][current_position]->set_quantity(
                                Mother[second_list - 1][current_position]->get_quantity() + Temp.get_quantity());
                    else                       /// if element is not in the list, the new object is put into the list
                        Mother[second_list - 1].add_new_element(Temp, second_number);
                    Mother[first_list - 1].remove_from_the_list(first_number);
                    std::cout << "The product was successfully moved\n";
                }
            }
        }
    }
}

void List_Manager::merge_two_lists() {
    int mother_size = Mother.size(), first_list, second_list = -1;
    if(mother_size < 2)     /// checks size of the vector containing list
        throw std::range_error("To merge lists you have to create at least two lists\n");
    do {
        try {
            first_list = -1;
            std::cout << "Input number of first list\n";
            for(int i = 0; i < mother_size; i++)
                std::cout << i + 1 << " " << Mother.at(i).get_name() << std::endl;
            std::cout << "To go back to the main menu press 0\n";      /// it's possible to come back to main menu
            first_list = Interaction::get_choice(0, mother_size);
        }
        catch (const Bad_Input & bad_input){
            std::cout << bad_input.what();
        }
        catch (const std::invalid_argument & inv_arg){
            std::cout << "Pick a number!!!!\n";
        }
    }
    while(first_list < 0 || first_list > mother_size);

    do {
        mother_size = Mother.size();
        try {
            std::cout << "Input number of second list\n";
            for(int i = 0; i < mother_size; i++) {
                if(i != first_list - 1)    /// condition added not to write information about first_list, because it's illogical to merge list with itself :)
                    std::cout << i + 1 << " " << Mother.at(i).get_name() << std::endl;
            }
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
        if (Mother[first_list - 1].not_empty_list() && Mother[second_list - 1].not_empty_list()) { /// we are merging lists only if both are not empty
            if (Interaction::sure()) {
                if(Mother[first_list - 1].get_size() + Mother[second_list - 1].get_size() <= 10) { /// because max size of list in this program is 10, checks if second list should be deleted
                    Mother[first_list - 1].merge_lists(Mother[second_list - 1]); /// calling the merging function
                    remove((Mother[second_list - 1].get_name() + ".txt").c_str());  /// removes txt file with list
                    if (std::find(files.cbegin(), files.cend(), Mother[second_list - 1].get_name()) !=
                        files.end())  /// to avoid segmentation fault
                        files.erase(std::find(files.cbegin(), files.cend(), Mother[second_list - 1].get_name())); /// name of list deleted from vector
                    Mother.erase(Mother.begin() + second_list - 1); /// erases second list from the vector
                }
                else {
                    while(Mother[first_list - 1].get_size() < 10) {    /// products from top of the second list are being moved to the bottom of second list until first list if full (10 members)
                        Mother[first_list - 1].add_new_element(*Mother[second_list - 1][0], Mother[first_list - 1].get_size() + 1); /// moving from second to first list, position = size of first list + 1
                        Mother[second_list - 1].remove_from_the_list(1); /// removes first element from second list
                    }
                    try {
                        if(!Mother[second_list - 1].not_empty_list()) {
                            if (std::find(files.cbegin(), files.cend(), Mother[second_list - 1].get_name()) !=
                                files.end())
                                files.erase(std::find(files.cbegin(), files.cend(), Mother[second_list - 1].get_name()));
                        }
                    }
                    catch(const Invalid_List & invalid_list) {}
                }
            }
        }
        current_list = 1;
    }
    catch(const Invalid_List & invalid_list) {
        std::cout << invalid_list.what();
    }
}

void List_Manager::show_list() {
    int mother_size = Mother.size(), first_list = -1;
    if(mother_size == 0) /// empty vector contains zero lists
        throw std::range_error("You have not created any lists\n");
    else if(mother_size == 1) /// because vector contains only one list, only the one can be displayed
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
   std::cout << Mother[first_list - 1]; /// overloaded << operator to display object of List type
}

void List_Manager::save_all() { /// called with the end of the session
    for (auto &i : files) /// removes files with old lists
        remove((i + ".txt").c_str());
    for (auto & i: Mother) /// saves new lists to new files
        i.save_list();
    std::fstream file_holder("register.txt", std::ios::out | std::ios::trunc); /// truncated file content
    if(file_holder) {
        for (auto &i: Mother)  /// names of files and lists are being saved to file register.txt
            file_holder << i.get_name() << "\n";
        file_holder.close();
    }
}
