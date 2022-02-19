//
// Created by Admin on 12.03.2021.
//
#include <iostream>
#include "Product.h"

void Product::set_quantity(int arg) {
    quantity = arg;
}

int Product::get_quantity() const {
    return quantity;
}

std::string Product::get_name() const {
    return name;
}

std::string Product::get_unit() const {
    return unit;
}

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
    str << product->name << " ";
    if(product->quantity > 0)
        str << product->quantity << " " << product->unit << std::endl;
    return str;
}
