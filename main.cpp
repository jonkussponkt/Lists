#include <iostream>
#include "List.h"
#include "List_Manager.h"
#include "Interaction.h"

void hello() {
    int choice;
    int current_list = -1;
    Product Temp = Product("",0);
    List Temp_List;

    std::string name, unit;
    List_Manager::fill_the_vector();  ///puts into memory previously saved lists if they exist
    do {
        choice = -1;
        do {
            try {
                if (current_list > 0)
                    std::cout << "YOUR CURRENT LIST IS NR " << current_list << std::endl;

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

        switch(choice) {   ///MAIN MENU
            case 1:
                try {
                    List_Manager::pick_a_list();
                }
                catch(const Invalid_List & invalid_list) {
                    std::cout << invalid_list.what();
                }
                break;
            case 2:
                List_Manager::add_new_list();
                break;
            case 3:
                List_Manager::rename_current_list();
                break;
            case 4:
                List_Manager::add_new_elements();
                break;
            case 5:
                List_Manager::delete_whole_list();
                break;
            case 6:
                try {
                    List_Manager::delete_element();
                }
                catch(const Invalid_List & invalid_list) {
                    std::cout << invalid_list.what();
                }
                break;
            case 7:
                try {
                    List_Manager::move_between_lists();
                }
                catch(const Invalid_List & invalid_list) {
                    std::cout << invalid_list.what();
                }
                catch(const std::range_error & range_error) {
                    std::cout << range_error.what();
                }
                break;
            case 8:
                try {
                    List_Manager::merge_two_lists();
                }
                catch(const std::range_error & range_error) {
                    std::cout << range_error.what();
                }
                break;
            case 9:
                try {
                    List_Manager::show_list();
                }
                catch(const std::range_error & range_error) {
                    std::cout << range_error.what();
                }
                break;
            case 10:
                if(Interaction::sure()) {
                    List_Manager::save_all();
                    choice = -1;
                }
                break;
            default:
                break;
        }
    }
    while(choice != -1);
}

int main() {
    hello();
    return 0;
}
