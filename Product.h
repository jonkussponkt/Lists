//
// Created by Admin on 12.03.2021.
//

#ifndef LISTS_PRODUCT_H
#define LISTS_PRODUCT_H

#include <string>
#include <memory>

struct Product {
    std::string name;
    int quantity;
    std::shared_ptr<Product> previous;
    std::shared_ptr<Product> next;
    friend std::ostream & operator<<(std::ostream & str, const std::shared_ptr<Product> & product);
    explicit Product(std::string str = "", int number = 0) : name(std::move(str)), quantity(number){
        previous = nullptr;
        next = nullptr;
    }
    Product(const Product & product);
    Product & operator=(const Product & product);
    ~Product() = default;
};



#endif //LISTS_PRODUCT_H
