//
// Created by Admin on 12.03.2021.
//

#include <iostream>
#include <string>
#include "List.h"


int List::get_size() const {
    return size;
}

bool List::full_list() const {
    return size >= 10;
}

bool List::not_empty_list() const {
    bool valid = size > 0;
    if (!valid)
        throw Invalid_List();
    return valid;
}

std::string List::get_name() const {
    return name;
}

int List::is_in_the_list(const std::string & product) const {
    int index = 0;
    std::shared_ptr<Product> Temp = first;
    while(Temp) {                   /// loop checks if product of name specified in 'product' variable is in the list, if so it returns its position from the head
        if(product == Temp->name)
            return index;
        Temp = Temp->next;   /// next element
        index++;            /// increments index of the list
    }
    return -1; /// -1 means that the list does not contain such product
}

void List::add_new_element(Product & new_element, int position) {
    std::shared_ptr<Product> Temp;
    std::shared_ptr<Product> Temp2;
    std::shared_ptr<Product> New_Product;
    int current_position = -1;
    if (size == 0) {
        first = std::make_shared<Product> (new_element);
        last = first;
    }
    else {
        New_Product = std::make_shared<Product> (new_element);
        current_position = is_in_the_list(New_Product->get_name()); /// checks if product is in the list and then, returns the position
        if(current_position > -1)     /// sums old and new quantity
            this->operator[](current_position)->set_quantity(this->operator[](current_position)->get_quantity() + New_Product->get_quantity());
        else if(position == 1) {        /// if adding into first position
            Temp = first;               /// old first is becoming temporary object
            first = New_Product;        /// new first element
            first->next = Temp;         /// old first element becomes next to new first
            Temp->previous = first;     /// new first element becomes the previous element to the old first element
        }
        else if(position == size + 1) { /// if adding at last position
            Temp = last;                /// old last is becoming temporary object
            last = New_Product;         /// new last object
            last->previous = Temp;      /// old last is becoming previous to new last
            Temp->next = last;          /// new last is becoming next to old last
        }
        else {                                  /// if adding at specific position, at first getting the two elements, that new object will be put between
            Temp = this->operator[](position - 1);      /// temporary previous element
            Temp2 = this->operator[](position - 2);     /// previous to Temp
            New_Product->next = Temp;           /// Temp element is becoming next to New_Product
            New_Product->previous = Temp2;      /// Temp2 element is becoming previous to New_Product
            Temp->previous = New_Product;       /// New_Product is becoming previous to Temp
            Temp2->next = New_Product;          /// New_Product is becoming next to Temp2
        }   /// now New_Product is put between Temp and Temp2 and connected to both of them from two sides
    }
    size++;
}

void List::remove_from_the_list(int position) {
    std::shared_ptr<Product> Temp1;
    std::shared_ptr<Product> Temp2;
    if(position == 1) {   /// if first element should be deleted
        if(size == 1) {       /// if this is the only one element, first and last are assigned to nullptr
            first = nullptr;
            last = nullptr;
        }
        else {
            first = first->next;        /// otherwise, second element becomes first and previous element to second element is null
            first->previous = nullptr;
        }
    }
    else if(position == size) {     /// if last element is to be deleted
        last = last->previous;          /// previous element to the last becomes new last
        last->next = nullptr;           /// old last becomes null
    }
    else {                          /// if element on specified position is to be deleted, at first we get elements between this one to be deleted
        Temp1 = this->operator[](position - 2);     ///
        Temp2 = this->operator[](position);                ///
        Temp1->next = Temp2;                /// Temp2 is becoming next to Temp1
        Temp2->previous = Temp1;            /// Temp1 is becoming previous to Temp2
    }
    size--;    /// size of the list becomes decremented
}

void List::merge_lists(List & to_merge) {
    bool is;
    std::shared_ptr<Product> Temp;   /// first list
    std::shared_ptr<Product> Temp_Guest = to_merge.first; /// second list
    while(Temp_Guest) {        /// goes through the second list
        is = false;
        Temp = first;
        while (Temp) {
            if (Temp_Guest->name == Temp->name) {
                is = true;   /// if element from the second list is on the first list, its quantity from the first and the second list are added
                Temp->quantity += Temp_Guest->quantity;
                break;
            }
            Temp = Temp->next;
        }
        if (!is)  /// if element does not exist on the first list, element from the second list is moved to the first list
            add_new_element(*Temp_Guest, size + 1);
        Temp_Guest = Temp_Guest->next;
    }
    to_merge.remove_from_the_list(1);
}

void List::set_name(const std::string & new_name) {
    name = new_name;
}

void List::save_list() const {
    try {
        if (not_empty_list()) {  /// to throw an exception
            std::fstream file_holder;
            file_holder.open(this->name + ".txt", std::ios::out | std::ios::trunc);
            if(!file_holder)
                std::cout << "Bad file!";
            else {
                std::shared_ptr<Product> Temp = first;
                while(Temp) {  /// saves to file all class members
                    file_holder << Temp->get_name() << "," << Temp->get_quantity() << "," << Temp->get_unit() << "\n";
                    Temp=Temp->next;
                }
                file_holder.close();
            }
        }
    }
    catch(const Invalid_List & invalid_list) {}
}

void List::read_list(const std::string & list_name) {
    std::fstream file_holder(list_name + ".txt");
    if(!file_holder)
        std::cout << "Bad file!\n";
    else {
        int first_char, second_char, prod_quantity;
        std::string element, prod_name, prod_unit;
        Product product = Product("", 0);
        int counter = 1;
        while(std::getline(file_holder,element)) {  /// loop parses every line in txt file
            first_char = element.find_first_of(',', 0);  /// comma is a separator of data, first field of each line is name
            second_char = element.find_first_of(',', first_char); ///  second field is quantity
            prod_name = element.substr(0, first_char);   /// get first element
            prod_quantity = std::stoi(element.substr(first_char + 1, second_char)); /// conversion to integer
            prod_unit = element.substr(second_char + 1, element.length());       /// unit is last part of line from text file
            product = Product(prod_name, prod_unit, prod_quantity);   /// creating new product
            add_new_element(product, counter);    /// adding new element into correct position
            counter++;
        }
        file_holder.close();
    }
}

std::ostream & operator << (std::ostream & str, const List & list) {
    int ID = 1;
    std::shared_ptr<Product> Temp = list.first;
    str << list.name << std::endl;
    while(Temp) {
        str << ID << " " << Temp;
        Temp = Temp->next;
        ID++;
    }
    return str;
}

std::shared_ptr<Product> List::operator[](int position) {
    int i;
    std::shared_ptr<Product> Temp;
    if(position <= size / 2) {   /// starts searching from first element if position is in first half of the list
        i = 0;
        Temp = first;
        while (i < position && Temp) {  /// goes through elements of the list from the head
            Temp = Temp->next;
            i++;
        }
    }
    else {                      /// starts searching from last element if position is in second half of the list
        i = size - 1;
        Temp = last;
        while(i > position && Temp){
            Temp = Temp->previous;   /// goes through elements of the list from the end
            i--;
        }
    }
    return Temp;
}

