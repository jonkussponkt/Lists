#include <iostream>
#include <vector>
#include "List.h"
#include "Interaction.h"

void hello() {
    int choice, first_list = -1, first_number = -1, second_list = -1, second_number = -1;
    int pos, ID, current_list = -1, temp_number, new_elements = -1, element;
    int type_of_product;
    Product Temp = Product("",0);
    List Temp_List;
    std::string name, unit;
    std::vector<List> Mother;
    do {
        ID = 1;
        choice = -1;
        do {
            try {
                if (current_list > 0) {
                    std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                }
                std::cout << "Input your choice!\n1 - To pick a list\n2 - To add a new list\n"
                             "3 - To rename the current list\n4 - To add new elements to currently chosen list\n"
                             "5 - To delete whole list\n6 - To delete element from a currently chosen list\n"
                             "7 - To move product from currently chosen list to another\n"
                             "8 - To merge two lists\n9 - To show the chosen list\n10 - To exit the program\n";
                choice = Interaction::get_choice(1, 10);
            }
            catch(const Bad_Input & bad_input) {
                std::cout << bad_input.what();
            }
            catch(const std::invalid_argument & inv_arg) {
                std::cout << "Pick a number!!!!\n";
            }
        }
        while(choice < 1 || choice > 10);

        switch(choice) {
            case 1:
                for(auto & i : Mother) {
                    std::cout << ID << " " << i.get_name() << std::endl;
                    ID++;
                }
                if(Mother.empty()) {
                    std::cout << "You have not created any list. Choose once more.\n";
                    break;
                }
                else if(Mother.size() == 1)
                    current_list = 1;
                else {
                    try {
                        do {
                            std::cout << "Pick ID number of list:\n";
                            current_list = Interaction::get_choice(1, Mother.size());
                        }
                        while(current_list < 1 || current_list > Mother.size());
                    }
                    catch (const Bad_Input & bad_input){
                        std::cout << bad_input.what();
                    }
                    catch (const std::invalid_argument & inv_arg){
                        std::cout << "Pick a number!!!!\n";
                    }
                }
                break;
            case 2:
                if(current_list > 0)
                    std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                else
                    std::cout << "You have not created any list\n";
                std::cout << "Input name of the list\n";
                while(name.empty()) {
                    try {
                        name = Interaction::get_str();
                    }
                    catch (const Bad_Input &bad_input) {
                        std::cout << bad_input.what();
                    }
                }
                Temp_List = List(name);
                Mother.push_back(Temp_List);
                current_list = Mother.size();

                name.clear();
                break;
            case 3:
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
                break;
            case 4:
                if(current_list > 0) {

                    temp_number = Mother[current_list - 1].get_size();
                    std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                    do {
                        try {
                            if(!Mother[current_list - 1].full_list()) {
                                std::cout << "How many elements (1-" << 10 - temp_number
                                          << ") do you want to add to the list nr " << current_list << "\n";
                                std::cout << "To go back to the main menu press 0\n";
                                new_elements = Interaction::get_choice(0, 10 - temp_number);
                            }
                        }
                        catch (const Bad_Input &bad_input) {
                            std::cout << bad_input.what();
                        }
                        catch (const std::invalid_argument &inv_arg) {
                            std::cout << "Pick a number!!!!\n";
                        }
                    }
                    while (new_elements < 0 || new_elements > 10 - temp_number);

                    element = 1;
                    if(new_elements > 0) {
                        while (element <= new_elements) {
                            std::cout << Mother[current_list - 1];
                            std::cout << "Input name of product nr " << element << " \n";
                            std::cout << "Press enter to come back to main menu\n";
                            try {
                                name = Interaction::get_str();
                            }
                            catch (const Bad_Input & bad_input) {

                            }

                            if (name.empty()) {
                                new_elements = -1;
                                break;
                            }
                            do {
                                try {
                                    std::cout << "Input quantity\n";
                                    first_number = Interaction::simply_get_int();
                                    std::cout << "Input unit if necessary, otherwise press enter\n";
                                    try {
                                        unit = Interaction::get_str();
                                    }
                                    catch(const Bad_Input & bad_input) {};
                                }
                                catch (const Bad_Input & bad_input) {
                                    std::cout << bad_input.what();
                                }
                                catch (const std::invalid_argument & inv_arg) {
                                    std::cout << "Pick a number!!!!\n";
                                }
                            }
                            while (first_number < 1);

                            //  todo nie dziala wyswietlanie jednostek

                            Temp = Product(name, unit, first_number);

                            if (temp_number == 0) {
                                Mother[current_list - 1].add_new_element(Temp, 1);
                                temp_number++;
                                element++;
                            }
                            else {
                                pos = Mother[current_list - 1].is_in_the_list(Temp.name);
                                if(pos == -1) {
                                    do {
                                        try {
                                            pos = -1;
                                            std::cout << "Input position of the element in the list (1-"
                                                      << temp_number + 1
                                                      << ")\nTo set product at the end of the list press "
                                                      << temp_number + 1
                                                      << std::endl;
                                            pos = Interaction::get_choice(1, temp_number + 1);
                                            Mother[current_list - 1].add_new_element(Temp, pos);
                                            temp_number++;
                                            element++;
                                        }
                                        catch (const Bad_Input &bad_input) {
                                            std::cout << bad_input.what();
                                        }
                                        catch (const std::invalid_argument &inv_arg) {
                                            std::cout << "Pick a number!!!!\n";
                                        }
                                    }
                                    while (pos < 1 || pos > temp_number);
                                }
                                else {
                                    std::cout << "You've already put this item on the list. Do you want to sum it with quantity of ";
                                    std::cout << Temp.get_name() << " (" << Mother[current_list - 1][pos]->get_quantity() << ")?\n"; /// wyśwqietla ilośc produktu
                                    if(Interaction::sure()) {
                                        Mother[current_list - 1][pos]->set_quantity(
                                                Mother[current_list - 1][pos]->get_quantity() + first_number);
                                        element++;
                                    }
                                }
                            }
                            //elements++;
                            //temp_number++;
                            Temp_List.clear();
                            name.clear();
                        }
                    }
                }
                else
                    std::cout << "You have not created any list\n";
                break;

            case 5:
                temp_number = Mother.size();
                if(temp_number == 0)
                    std::cout << "You have not created any lists\n";
                else if(temp_number == 1)
                    first_list = 1;
                else {
                    do {
                        try {
                            std::cout << "Input number of list you want to remove\n";
                            if (temp_number < 2) {
                                first_list = Interaction::simply_get_int();
                                temp_number = 2;
                            }
                            else
                                first_list = Interaction::get_choice(1, temp_number);
                        }
                        catch (const Bad_Input &bad_input) {
                            std::cout << bad_input.what();
                        }
                        catch (const std::invalid_argument &inv_arg) {
                            std::cout << "Pick a number!!!!\n";
                        }
                    }
                    while (first_list < 1 && first_list > temp_number);
                }
                if(temp_number > 0 && Interaction::sure()) {
                    Mother.erase(Mother.begin() + first_list - 1);
                    if (first_list == current_list)
                        current_list = -1;
                }
                break;

            case 6:
                if(Mother.size() > 0) {
                    first_list = current_list;
                    temp_number = Mother[first_list - 1].get_size();
                    std::cout << Mother[first_list - 1];

                    if (temp_number == 0) {
                        std::cout << "The list is empty\n";
                        break;
                    } else if (temp_number == 1)
                        first_number = 1;
                    else {
                        do {
                            try {
                                if (current_list > 0)
                                    std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                                std::cout << "Input position of element you want to remove\n";
                                first_number = Interaction::get_choice(1, temp_number);
                            }
                            catch (const Bad_Input &bad_input) {
                                std::cout << bad_input.what();
                            }
                            catch (const std::invalid_argument &inv_arg) {
                                std::cout << "Pick a number!!!!\n";
                            }
                        } while (first_number < 1 || first_number > temp_number);
                    }
                    if (Interaction::sure()) {
                        Mother[first_list - 1].remove_from_the_list(first_number);
                        std::cout << "The product was successfully removed\n";
                    }
                }
                else
                    std::cout << "You have not created any list\n";
                break;

            case 7:
                if(Mother.size() < 2) {
                    std::cout << "To move products between lists you have to create at least two lists\n";
                    break;
                }
                else {
                    first_list = current_list;
                    temp_number = Mother[first_list - 1].get_size();
                    if (temp_number < 1) {
                        std::cout << "The list is empty\n";
                        break;
                    }
                    else {
                        do {
                            try {
                                if (current_list > 0) {
                                    std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;
                                    std::cout << Mother[current_list - 1];
                                }
                                std::cout << "Input number of product\n";
                                first_number = Interaction::get_choice(1, temp_number);
                            }
                            catch (const Bad_Input &bad_input) {
                                std::cout << bad_input.what();
                            }
                            catch (const std::invalid_argument &inv_arg) {
                                std::cout << "Pick a number!!!!\n";
                            }
                        }
                        while (first_number < 1 || first_number > temp_number);

                        Temp = *Mother[first_list - 1][first_number - 1];

                        temp_number = Mother.size();
                        if (temp_number < 2) {
                            std::cout << "You have not created at least 2 lists\n";
                            break;
                        }
                        do {
                            try {
                                std::cout << "Input number of list where you want to move product:\n";
                                second_list = Interaction::get_choice(1, temp_number);
                            }
                            catch (const Bad_Input &bad_input) {
                                std::cout << bad_input.what();
                            }
                            catch (const std::invalid_argument &inv_arg) {
                                std::cout << "Pick a number!!!!\n";
                            }
                        }
                        while (second_list < 1 || second_list > temp_number || second_list == first_list);

                        temp_number = Mother[second_list - 1].get_size();
                        int current_position = Mother[second_list - 1].is_in_the_list(Temp.get_name());

                        if(current_position == -1) {
                            if (temp_number == 0)
                                second_number = 1;
                            else if (temp_number == 1)
                                second_number = 2;
                            do {
                                try {
                                    std::cout << "Input position of the product on the list nr " << second_list;
                                    std::cout << std::endl << Mother[second_list - 1];
                                    second_number = Interaction::get_choice(1, temp_number + 1);
                                }
                                catch (const Bad_Input &bad_input) {
                                    std::cout << bad_input.what();
                                }
                                catch (const std::invalid_argument &inv_arg) {
                                    std::cout << "Pick a number!!!!\n";
                                }
                            }
                            while (second_number < 1 || second_number > temp_number);
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
                break;
            case 8:
                temp_number = Mother.size();
                if(temp_number < 2) {
                    std::cout << "To merge lists you have to create at least two lists\n";
                    break;
                }
                do {
                    try {
                        first_list = -1;
                        std::cout << "Input number of first list\n";
                        first_list = Interaction::get_choice(1, temp_number);
                    }
                    catch (const Bad_Input & bad_input){
                        std::cout << bad_input.what();
                    }
                    catch (const std::invalid_argument & inv_arg){
                        std::cout << "Pick a number!!!!\n";
                    }
                }
                while(first_list < 1 || first_list > temp_number);

                do {
                    temp_number = Mother.size();
                    try {
                        std::cout << "Input number of second list\n";
                        second_list = Interaction::get_choice(1, temp_number);
                    }
                    catch (const Bad_Input & bad_input){
                        std::cout << bad_input.what();
                    }
                    catch (const std::invalid_argument & inv_arg){
                        std::cout << "Pick a number!!!!\n";
                    }
                }
                while(second_list < 1 || second_list > temp_number || second_list == first_list);

                std::cout << "Second list \"" << Mother.at(second_list - 1).get_name() << "\" will be deleted after merging\n";
                if(Interaction::sure()) {
                    if(!Mother[second_list - 1].empty_list())
                        Mother[first_list - 1].merge_lists(Mother[second_list - 1]);
                    Mother.erase(Mother.begin() + second_list - 1);
                    current_list = second_list - 1;
                }
                break;
            case 9:
                temp_number = Mother.size();
                if(temp_number == 0) {
                    std::cout << "You have not created any lists\n";
                    break;
                }
                else if(temp_number == 1)
                    first_list = 1;
                else {
                    do {
                        try {
                            std::cout << "Input number of list:\n";
                            for(int i = 0; i < temp_number; i++)
                                std::cout << i + 1 << " " << Mother.at(i).get_name() << std::endl;
                            first_list = Interaction::get_choice(1, temp_number);
                        }
                        catch (const Bad_Input &bad_input) {
                            std::cout << bad_input.what();
                        }
                        catch (const std::invalid_argument &inv_arg) {
                            std::cout << "Pick a number!!!!\n";
                        }
                    }
                    while (first_list < 1 || first_list > temp_number);
                }
                std::cout << Mother[first_list - 1];
                break;
            case 10:
                if(Interaction::sure())
                    choice = -1;
                break;
            default:
                break;
        }
        first_list = -1;
        first_number = -1;
        second_list = -1;
        second_number = -1;
        pos = -1,
        temp_number = -1;
    }
    while(choice != -1);
}

int main() {
    hello();
    return 0;
}
