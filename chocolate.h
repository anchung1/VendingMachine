//
// Created by Anthony Chung on 9/2/16.
//

#ifndef VENDME_CHOCOLATE_H
#define VENDME_CHOCOLATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct choc_ {
    string keyID;  //can be used to decode location
    string name;
    int cost;  //unit in cents
    int quantity;

}Chocolate;

class VendChocolates {
    vector<Chocolate> items;

    vector<Chocolate>::iterator find_item(string id);
public:
    VendChocolates() {};
    void stockAllItems(int quantity=10);
    void removeAllItems();

    void addQuantity(string id, int quantity);
    void removeQuantity(string id, int quantity);

    void addNewItem(Chocolate &ch);
    void removeItem(string id);

    Chocolate* get_info(string id);
    const vector<Chocolate>& get_data();
    void report();
};

#endif //VENDME_CHOCOLATE_H
