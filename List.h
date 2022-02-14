//
// Created by Admin on 12.03.2021.
//

#ifndef LISTS_LIST_H
#define LISTS_LIST_H

#include <string>
#include <memory>
#include "Product.h"
#include "Interaction.h"

class List {
    std::string name;
    std::shared_ptr<Product> first;
    std::shared_ptr<Product> last;
    int size;
public:
    int get_size() const;
    bool full_list() const;
    bool empty_list() const;
    int is_in_the_list(const std::string & product) const;
    void add_new_element(Product & new_element, int position);
    void remove_from_the_list(int position);
    void merge_lists(List & to_merge);
    void set_name(const std::string & new_name);
    void clear();
    std::string get_name() const;
    std::shared_ptr<Product> operator [] (int position);
    explicit List(std::string new_name = "", int number = 0) : name(std::move(new_name)), size(number){
        first = nullptr;
        last = nullptr;
    }
    ~List() = default;

    friend std::ostream & operator << (std::ostream & str, const List & list);
};

#endif //LISTS_LIST_H
