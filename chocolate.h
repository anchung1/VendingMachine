//
// Created by Anthony Chung on 9/2/16.
//

#ifndef VENDME_CHOCOLATE_H
#define VENDME_CHOCOLATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Chocolate {
    string name;
    float cost;

public:
    Chocolate(string name, float cost): name(name), cost(cost){};
    bool is_name(string name) { return this->name.compare(name) == 0; }
    string get_name() {return name;}
    float get_cost() {return cost;}
    string to_string() {return name + " costs " + std::to_string(cost); }
};

extern Chocolate* get_chocolate_data(string name);

#endif //VENDME_CHOCOLATE_H
