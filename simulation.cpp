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
    if (locale == "US") coin_unit = "cents";
    if (locale == "UK") coin_unit = "pence";

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

    if (front.type == itemDataRequestEvent) {
        vendingMachine->get_item_data();
    }

    if (front.type == itemSelectEvent) {
        vendingMachine->select_item(front.s_data1);
    }

    if (front.type == sendCurrencyReport) {
        vendingMachine->send_currency_report();
    }
    if (front.type == sendItemsReport) {
        vendingMachine->send_items_report();
    }
    event_input_queue.pop();
}

void Simulation::process_output_queue() {
    string msg;

    //no output device, so we'll simulate that here
    while ( !event_output_queue.empty() ) {
        EventData front = event_output_queue.front();
        if (front.type == itemDataReportEvent) {
            cout << "#: " << front.s_data1 << " " << front.s_data2 << " "
                 << to_string(front.data) << coin_unit << endl;
        }
        if (front.type == coinEvent) {
            cout << "cash in: " << front.data << coin_unit << endl;
        }
        if (front.type == ejectCoinEvent) {
            cout << "ejecting: " << front.data << coin_unit << endl;
        }
        if (front.type == showFundsEvent) {
            cout << endl << "total credit: " << front.data << endl;
        }
        if (front.type == itemDispenseEvent) {
            cout << "DISPENSING ITEM: " << front.s_data2 << " from " << front.s_data1 << endl;
        }
        if (front.type == sendCurrencyReport) {
            //name, denomination, quantity
            cout << "Currency Report: " << front.s_data1 << " " << front.data << " " << front.data2 << endl;
        }
        if (front.type == sendItemsReport) {
            //keyID, name, cost, quantity
            cout << "Item Report: " << front.s_data1 << " " << front.s_data2 << " " << front.data << " " << front.data2 << endl;
        }
        event_output_queue.pop();
    }
}

void Simulation::preconfigure_vending_machine() {
    vendingMachine->stock_coins(1);
    vendingMachine->stock_items();

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
