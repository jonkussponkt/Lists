//
// Created by Admin on 12.03.2021.
//
#include <iostream>
#include "Product.h"

Product::Product(const Product &product) {
    name = product.name;
    quantity = product.quantity;
    previous = nullptr;
    next = nullptr;
}

Product & Product::operator=(const Product & product){
    if(this == &product)
        return *this;
    name = product.name;
    quantity = product.quantity;
    previous = nullptr;
    next = nullptr;
    return *this;
}

std::ostream & operator<<(std::ostream & str, const std::shared_ptr<Product> & product) {
    str << product->name << " " << product->quantity << std::endl;
    return str;
}
