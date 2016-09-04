//
// Created by Anthony Chung on 9/2/16.
//

#ifndef VENDME_VENDINGMACHINE_H
#define VENDME_VENDINGMACHINE_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include "events.h"
#include "coin.h"

using namespace std;

class Item {
    string name;
    float cost;
public:
    Item() {};
};

class VendingMachine {

    string locale;
    Coins *coins;
    int bill_count;

    //money collected during user interaction
    int credit_fund;
    int cash_fund;
    stack<int> coins_in;

    queue<EventData> event_queue;
    bool debug;

public:
    VendingMachine(string locale);

    //preconfigure before simulation
    void stock_items();
    void stock_coins(int quantity=10);

    //debug
    void showCoins();

    //API to check machine state
    bool accepting_bill(); //dollar coin needed for refund
    bool accepting_coins();
    bool exact_change_required();

    //API to receive funds
    bool insert_credit(int amount); //unit of cent
    bool insert_bill();  //assume only dollar bills are accepted
    bool insert_coin(int denomination); //hopefully device driver can detect denomination

    //API to eject funds
    void cancel_purchase();
    void cancel_credit(int total); //select item, then authorize to avoid credit cancel.
    void eject_coin(int denomination);

    //API to select an item
    bool select_item(int row, int col) {return true;} //some devices may opt for row/col selection
    bool select_item(string id); //row/col may be combined as an id

    //API to dispense item
    bool dispense_item(int row, int col);

    //inventory API to track state of machine
    bool send_currency_report(); //coins + bills reporting
    bool send_items_report(); //item name/count reporting

    //API for serviceman for adding/removing items,coins,bills?

    EventData get_event();
    //END public APIs

};


#endif //VENDME_VENDINGMACHINE_H
