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

void List::clear() {
    name.clear();
    first = nullptr;
    last = nullptr;
    size = 0;
}

void List::save_list(const std::string & name) const {
    try {
        if (not_empty_list()) {
            std::fstream file_holder;

        }
    }
    catch(const Invalid_List & invalid_list) {
        std::cout << invalid_list.what();
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
