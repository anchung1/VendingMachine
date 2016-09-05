//
// Created by Anthony Chung on 9/2/16.
//

#include "VendingMachine.h"
bool vending_debug = false;

VendingMachine::VendingMachine(string locale) :
        credit_fund(0), cash_fund(0), bill_count(0){
    this->debug = vending_debug;
    this->locale = locale;
    coins = get_coins(locale);
    chocolates = new VendChocolates();
}

VendingMachine::~VendingMachine() {
    delete chocolates;
    clean_up_coins();
}

void VendingMachine::stock_coins(int quantity) {
    coins->stockCoins(quantity);
    coins->showCoins();
}

void VendingMachine::stock_items() {
    chocolates->stockAllItems();
    if (debug) {
        chocolates->report();
    }

//
//    chocolates->addQuantity("c5", 2);
//    Chocolate *choc = chocolates->get_info("c5");
//    cout << choc->keyID << " " << choc->name << " " << choc->cost << " " << choc->quantity << endl;
//
//    chocolates->removeQuantity("c5", 3);
//    choc = chocolates->get_info("c5");
//    cout << choc->keyID << " " << choc->name << " " << choc->cost << " " << choc->quantity << endl;

}

void VendingMachine::increment_cash_fund(int sum) {
    cash_fund += sum;
    queue_event(coinEvent, cash_fund);
}

bool VendingMachine::insert_coin(int denomination) {
    increment_cash_fund(denomination);
    coins_in.push(denomination);
    return coins->insertCoin(denomination);
}

bool VendingMachine::insert_bill() {
    increment_cash_fund(coins->get_fat_coin_value());

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
    queue_event(coinEvent, 0);
}

void VendingMachine::cancel_credit(int total) {
    queue_event(creditEvent, total);
}

void VendingMachine::eject_coin(int denomination) {
    queue_event(ejectCoinEvent, denomination);
}

EventData VendingMachine::get_event() {
    if (event_queue.empty()) {
        return {noEvent, 0};
    }

    EventData front = event_queue.front();
//    if (debug) {
//        cout<< "get_event: " << to_string(front.type) << " " << to_string(front.data) << endl;
//    }
    event_queue.pop();
    return front;
}

void VendingMachine::get_item_data() {
    const vector<Chocolate>& choc = chocolates->get_data();

    for (auto it = choc.begin(); it < choc.end(); it++ ) {
        //cout << it->name << it->quantity << " "<< endl;
        queue_event(itemDataReportEvent, it->cost, 0, it->keyID, it->name);
    }

    queue_event(showFundsEvent, get_money_in());
}

void VendingMachine::send_currency_report() {
    const vector<coin>& coin_data = coins->get_data();

    for (auto it = coin_data.begin(); it < coin_data.end(); it++) {
        queue_event(sendCurrencyReport, it->denomination, it->quantity, it->name);
    }
}

void VendingMachine::send_items_report() {
    const vector<Chocolate>& choc = chocolates->get_data();

    for (auto it = choc.begin(); it< choc.end(); it++) {
        queue_event(sendItemsReport, it->cost, it->quantity, it->keyID, it->name);
    }

}

int VendingMachine::get_money_in() {
    return (credit_fund + cash_fund);
}

void VendingMachine::eject_change(list<int>& change) {

    while (!change.empty()) {
        int front = change.front();
        queue_event(ejectCoinEvent, front);
        change.pop_front();
    }
    change.clear();
}

void VendingMachine::select_item(string id) {
    Chocolate *choc = chocolates->get_info(id);
    if (!choc) return;

    int money_in = get_money_in();
    if (choc->cost > money_in) {
        cout << "Insufficient funds." << endl;
        return;
    }
    if (choc->quantity == 0) {
        cout << choc->name << " is not available." << endl;
        return;
    }

    //check if we can make change before proceeding
    list<int> change;
    if (money_in != choc->cost) {
        change = coins->make_change(money_in - choc->cost);
        if (change.empty()) {
            cout << "Please use exact change." << endl;
            cancel_purchase();
            return;
        }
    }

    queue_event(itemDispenseEvent, 0, 0, id, choc->name);
    choc->quantity--;
    eject_change(change);

    while( !coins_in.empty() ) {
        coins_in.pop();
    }
    cash_fund = 0;
}

//this API doesn't make a lot of sense in this simulation model
//where external devices (to remove item from inventory) are reached
//via (serial port) events.
void VendingMachine::dispense_item(string id) {
}

//nice to have one place to push out events
//in case event data structure changes.
void VendingMachine::queue_event(VendingEvent ev, int data, int data1, string s_data1, string s_data2) {
    event_queue.push({ev, data, data1, s_data1, s_data2});
}