//
// Created by Anthony Chung on 9/2/16.
//

#include "VendingMachine.h"
bool vending_debug = true;

VendingMachine::VendingMachine(string locale) {
    this->debug = vending_debug;
    this->locale = locale;
    coins = get_coins(locale);
}

void VendingMachine::stock_coins(int quantity) {
    coins->stockCoins(quantity);
    coins->showCoins();
}

void VendingMachine::stock_items() {
    //TODO
}

bool VendingMachine::insert_coin(int denomination) {
    cash_fund += denomination;
    coins_in.push(denomination);
    return coins->insertCoin(denomination);
}

bool VendingMachine::insert_bill() {
    cash_fund += coins->get_fat_coin_value();

    //because we have to refund in coins
    coins_in.push(coins->get_fat_coin_value());

    bill_count++; //used for reporting
    return true;
}

bool VendingMachine::insert_credit(int amount) {
    //this assumes that card reader device handles
    //the authorization and rejection.

    //At this point, card has been authorized.
    credit_fund += amount;
    return true;
}

bool VendingMachine::accepting_bill() {
    //To accept bills, we have to have "dollar" coin
    //in case refund is requested.

    //TODO: handle case where multiple dollar coins
    //are needed to accept multiple bills

    return coins->has_fat_coin();
}

bool VendingMachine::accepting_coins() {
    //either cash or credit
    //can't mix

    if (credit_fund > 0) return false;
    return true;
}

void VendingMachine::showCoins() {
    if (!debug) return;

    coins->showCoins();
}

void VendingMachine::cancel_purchase() {
    //either cash or credit, not both
    if (cash_fund > 0) {
        while( !coins_in.empty() ) {
            int top = coins_in.top();
            coins->removeCoin(top);
            eject_coin(top);
            coins_in.pop();
        }
    } else if(credit_fund > 0) {
        cancel_credit(credit_fund);
    }

    credit_fund = 0;
    cash_fund = 0;
}

void VendingMachine::cancel_credit(int total) {
    event_queue.push({creditEvent, total});
}

void VendingMachine::eject_coin(int denomination) {
    event_queue.push({ejectCoinEvent, denomination});
}

EventData VendingMachine::get_event() {
    if (event_queue.empty()) {
        return {noEvent, 0};
    }

    EventData front = event_queue.front();
    if (debug) {
        cout<< "get_event: " << to_string(front.type) << " " << to_string(front.data) << endl;
    }
    event_queue.pop();
    return front;
}
