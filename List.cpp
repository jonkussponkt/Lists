//
// Created by Admin on 12.03.2021.
//

#include <iostream>
#include <string>
#include "List.h"

int List::get_size() const {
    return size;
}

std::string List::get_name() const {
    return name;
}

void List::add_new_element(Product & new_element, int position) {
    std::shared_ptr<Product> Temp;
    std::shared_ptr<Product> Temp2;
    std::shared_ptr<Product> New_Product;
    if (size == 0) {
        first = std::make_shared<Product> (new_element);
        last = first;
    }
    else {
        New_Product = std::make_shared<Product> (new_element);
        if(position == 1){
            Temp = first;
            first = New_Product;
            first->next = Temp;
            Temp->previous = first;
        }
        else if(position == size + 1){
            Temp = last;
            last = New_Product;
            last->previous = Temp;
            Temp->next = last;
        }
        else {
            Temp = this->operator[](position);
            Temp2 = this->operator[](position - 1);
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
    if(position == 1){
        if(size == 1) {
            first = nullptr;
            last = nullptr;
        }
        else {
            first = first->next;
            first->previous = nullptr;
        }
    }
    else if(position == size){
        last = last->previous;
        last->next = nullptr;
    }
    else {
        Temp1 = this->operator[](position - 1);
        Temp2 = this->operator[](position + 1);
        Temp1->next = Temp2;
        Temp2->previous = Temp1;
    }
    size--;
}

void List::merge_lists(List & to_merge){
    bool is;
    std::shared_ptr<Product> Temp;
    std::shared_ptr<Product> Temp_Guest = to_merge.first;
    while(Temp_Guest){
        is = false;
        Temp = first;
        while(Temp){
            if(Temp_Guest->name == Temp->name) {
                is = true;
                Temp->quantity += Temp_Guest->quantity;
            }
            Temp = Temp->next;
        }
        if(!is)
            add_new_element(*Temp_Guest,size + 1);
        Temp_Guest = Temp_Guest->next;
        to_merge.remove_from_the_list(1);
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
        i = 1;
        Temp = first;
        while (i < position && Temp) {
            Temp = Temp->next;
            i++;
        }
    }
    else {
        i = size;
        Temp = last;
        while(i > position && Temp){
            Temp = Temp->previous;
            i--;
        }
    }
    return Temp;
}
