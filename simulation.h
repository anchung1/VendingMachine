//
// Created by Anthony Chung on 9/3/16.
//

#ifndef VENDME_SIMULATION_H
#define VENDME_SIMULATION_H

#include "menu.h"
#include "VendingMachine.h"
#include "events.h"
#include <queue>

class Simulation {
    queue<EventData> event_input_queue;
    queue<EventData> event_output_queue;

    Menu *menu;
    VendingMachine *vendingMachine;

    string locale;
    string coin_unit;
    bool debug;

    void process_input_queue();
    void process_output_queue();

    void preconfigure_vending_machine();

public:
    Simulation() : debug(false) {};
    void set_localization(string local);
    ~Simulation() {
        delete menu;
        delete vendingMachine;
    }
    void simulate();
};


#endif //VENDME_SIMULATION_H
