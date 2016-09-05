//
// Created by Anthony Chung on 9/2/16.
//

#include "chocolate.h"

vector<Chocolate> item_data = {
        {"a1", "100 Grand Bar", 65, 0}, {"a2", "3 Musketeers", 65, 0}, {"a3", "5th Avenue", 65, 0}, {"a4", "Almond Joy", 65, 0}, {"a5", "Baby Ruth", 65 , 0},
        {"b1", "Butterfinger", 75, 0}, {"b2", "Chunky", 75, 0}, {"b3", "Clark Bar", 75, 0}, {"b4", "Dove Bar", 75, 0}, {"b5", "Heath Bar", 75, 0},
        {"c1", "Hershey's", 85, 0}, {"c2", "Kit Kat", 85, 0}, {"c3", "Krackel", 85, 0}, {"c4", "Marathon", 85, 0}, {"c5", "Milky Way", 85, 0} };


void VendChocolates::stockAllItems(int quantity) {
    vector<Chocolate>::iterator idi;

    for(idi=item_data.begin(); idi < item_data.end(); idi++) {
        idi->quantity = quantity;
        items.push_back(*idi);
    }

}

void VendChocolates::removeAllItems() {
    items.erase(items.begin(), items.end());
}

vector<Chocolate>::iterator
VendChocolates::find_item(string id) {
    vector<Chocolate>::iterator it;

    for (it = items.begin(); it < items.end(); it++) {
        if (it->keyID == id) {
            return it;
        }
    }

    return it;
}

void VendChocolates::addQuantity(string id, int quantity) {

    auto it = find_item(id);
    if (it >= items.end() ) {
        return;
    }

    it->quantity += quantity;
}

void VendChocolates::removeQuantity(string id, int quantity) {
    auto it = find_item(id);
    if (it >= items.end()) {
        return;
    }

    it->quantity -= quantity;
    if (it->quantity < 0) {
        it->quantity = 0;
    }
}

Chocolate* VendChocolates::get_info(string id) {
    auto it = find_item(id);
    if (it >= items.end()) {
        return nullptr;
    }

    return (Chocolate*)&(it->keyID);
}

void VendChocolates::addNewItem(Chocolate &ch) {
    items.push_back({ch.keyID, ch.name, ch.cost, ch.quantity});
}

void VendChocolates::removeItem(string id) {
    auto it = find_item(id);
    if ( it >= items.end()) {
        return;
    }

    items.erase(it);
}

const vector<Chocolate>& VendChocolates::get_data() {
    return items;
}

void VendChocolates::report() {
    for(auto idi=items.begin(); idi < items.end(); idi++) {
        cout << idi->keyID << " " << idi->name << " " << idi->cost << " " <<idi->quantity << endl;
    }
}

