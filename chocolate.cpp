//
// Created by Anthony Chung on 9/2/16.
//

#include "chocolate.h"

vector<Chocolate> chocolate_data;
struct UserData {
    string name;
    float cost;
};
UserData user_data[] = { {"Baby Ruth", 0.50}, {"Milky Way", 0.65}, {"Mars", 0.60} };

void pack_choc_data() {
    int length = sizeof(user_data) / sizeof(struct UserData);
    for (int i=0; i<length; i++) {
        chocolate_data.push_back(Chocolate(user_data[i].name, user_data[i].cost));
    }
}

Chocolate* get_chocolate_data(string name) {

    vector<Chocolate>::iterator cit;
    if (chocolate_data.size() == 0) {
        pack_choc_data();
    }

    for (cit = chocolate_data.begin(); cit != chocolate_data.end(); cit++) {
        if (cit->is_name(name)) {
            return &(*cit);
        }
    }

    return nullptr;
}
