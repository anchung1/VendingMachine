//
// Created by Anthony Chung on 9/3/16.
//

#include "simulation.h"
#include <list>

list<string> supported_local = {"US", "UK"};
void Simulation::set_localization(string symbol) {
    //start with default
    string locale = "US";

    for(string sl: supported_local) {
        if (sl.compare(symbol) == 0) {
            locale = sl;
        }
    }

    cout << "Using locale: " << locale << endl;
    this->locale = locale;
    menu = get_menu(locale);
    vendingMachine = new VendingMachine(locale);
}

void Simulation::process_input_queue() {
    if (event_input_queue.empty()) return;

    EventData front = event_input_queue.front();

    if (front.type == coinEvent) {
        vendingMachine->insert_coin(front.data);
        if (debug) {
            vendingMachine->showCoins();
        }
    }

    if (front.type == refundMenuEvent ) {
        vendingMachine->cancel_purchase();
    }

    event_input_queue.pop();
}

void Simulation::process_output_queue() {
    string msg;

    while ( !event_output_queue.empty() ) {
        EventData front = event_output_queue.front();
        msg = translate_event(front);
        cout << "Output Event to devices: " << msg << endl;
        event_output_queue.pop();
    }
}

void Simulation::preconfigure_vending_machine() {
    vendingMachine->stock_coins();
}

void Simulation::simulate() {
    EventData event;

    preconfigure_vending_machine();

    while(1) {
        //interact with user
        menu->show_menu();
        menu->get_menu_selection();

        //check for user event
        //user inputs come in one at a time.
        event = menu->get_menu_event();
        if (event.type == quitMenuEvent) {
            break;
        }

        if (event.type != noEvent) {
            event_input_queue.push(event);
        }

        //process user event
        process_input_queue();

        //an input event can trigger multiple
        //output events.
        while (1) {
            event = vendingMachine->get_event();
            if (event.type == noEvent) break;

            event_output_queue.push(event);
        }

        //events to external devices
        process_output_queue();
    }

}
