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
    while(Temp) {
        if(product == Temp->name)
            return index;
        Temp = Temp->next;
        index++;
    }
    return -1;
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
        current_position = is_in_the_list(New_Product->get_name());
        if(current_position > -1)
            this->operator[](current_position)->set_quantity(this->operator[](current_position)->get_quantity() + New_Product->get_quantity());
        else if(position == 1) {
            Temp = first;
            first = New_Product;
            first->next = Temp;
            Temp->previous = first;
        }
        else if(position == size + 1) {
            Temp = last;
            last = New_Product;
            last->previous = Temp;
            Temp->next = last;
        }
        else {
            Temp = this->operator[](position - 1);
            Temp2 = this->operator[](position - 2);
            New_Product->next = Temp;
            New_Product->previous = Temp2;
            Temp->previous = New_Product;
            Temp2->next = New_Product;
        }
    }
    size++;
}

void List::remove_from_the_list(int position) {
    std::shared_ptr<Product> Temp1;
    std::shared_ptr<Product> Temp2;
    if(position == 1) {
        if(size == 1) {
            first = nullptr;
            last = nullptr;
        }
        else {
            first = first->next;
            first->previous = nullptr;
        }
    }
    else if(position == size) {
        last = last->previous;
        last->next = nullptr;
    }
    else {
        Temp1 = this->operator[](position - 2);
        Temp2 = this->operator[](position);
        Temp1->next = Temp2;
        Temp2->previous = Temp1;
    }
    size--;
}

void List::merge_lists(List & to_merge) {
    bool is;
    std::shared_ptr<Product> Temp;
    std::shared_ptr<Product> Temp_Guest = to_merge.first;
    //if(!this->not_empty_list() && !to_merge.not_empty_list())
    while(Temp_Guest) {
        is = false;
        Temp = first;
        while (Temp) {
            if (Temp_Guest->name == Temp->name) {
                is = true;
                Temp->quantity += Temp_Guest->quantity;
                break;
            }
            Temp = Temp->next;
        }
        if (!is)
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
        if (not_empty_list()) {  //only to throw an exception if empty
            std::fstream file_holder;
            file_holder.open(this->name + ".txt", std::ios::out | std::ios::trunc);
            if(!file_holder)
                std::cout << "Bad file!";
            else {
                std::shared_ptr<Product> Temp = first;
                while(Temp) {
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
        while(std::getline(file_holder,element)) {
            first_char = element.find_first_of(',', 0);
            second_char = element.find_first_of(',', first_char);
            prod_name = element.substr(0, first_char);
            prod_quantity = std::stoi(element.substr(first_char + 1, second_char));
            prod_unit = element.substr(second_char + 1, element.length());
            product = Product(prod_name, prod_unit, prod_quantity);
            add_new_element(product, counter);
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
    if(position <= size / 2) {
        i = 0;
        Temp = first;
        while (i < position && Temp) {
            Temp = Temp->next;
            i++;
        }
    }
    else {
        i = size - 1;
        Temp = last;
        while(i > position && Temp){
            Temp = Temp->previous;
            i--;
        }
    }
    return Temp;
}

