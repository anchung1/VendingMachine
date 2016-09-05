//
// Created by Anthony Chung on 9/3/16.
//

#include "menu.h"
bool debug = true;

void Menu::show_main_menu() {
    valid_actions.clear();

    cout << "Select an action: " << endl;
    cout << "a) Add Coin" << endl;
    cout << "b) Select Item" << endl;
    cout << "c) Refund" << endl;
    cout << "d) Quit" << endl;
    if (debug) {
        cout << "e) send_currency_report (debug)" << endl;
        cout << "f) send_items_report (debug)" << endl;
    }
    cout << "Enter 'a', 'b', 'c' or 'd': " << endl;

    add_valid_action("a");
    add_valid_action("b");
    add_valid_action("c");
    add_valid_action("d");
    if (debug) {
        add_valid_action("e");
        add_valid_action("f");
    }
}

void Menu::show_item_menu() {
    //need to send out a message to vending machine
    //to show its inventory

    valid_actions.clear();
    add_valid_action("all");
}

void Menu::show_menu() {

    if (menuState == mainMenu) {
        show_main_menu();
    }

    if (menuState == addCoin) {
        show_coin_menu();
    }

    if (menuState == selectItem) {
        show_item_menu();
    }

}

void Menu::add_valid_action(string input) {
    string lower = input;

    for (int i=0; i<lower.size(); i++) {
        lower[i] = (char)tolower(lower[i]);
    }

    //just support lower case
    valid_actions.push_back(lower);
}

void Menu::get_menu_selection() {
    string selection;

    if (menuState == selectItem) {
        cout << "Please select code after #: " << endl;
    }
    cin >> selection;

    //convert user input to lower case
    for (int i=0; i<selection.size(); i++) {
        selection[i] = (char)tolower(selection[i]);
    }

    bool valid = check_valid_input(selection);
    if (!valid) {
        cout << "Bad input.  Try again." << endl;
        return get_menu_selection();
    } else {
        do_action(selection);
        //show_menu();
        cout << "selection: " << selection << endl;
    }
}

bool Menu::do_action(string select) {
    bool ret_val = false;

    if (menuState == mainMenu) {
        ret_val = true;

        if (select == "a") {
            menuState = addCoin;
        }
        if (select == "b") {
            menuState = selectItem;
            queue_event(itemDataRequestEvent);
        }
        if (select == "c") {
            queue_event(refundMenuEvent);
        }
        if (select == "d") {
            queue_event(quitMenuEvent);
        }
        if (select == "e") {
            queue_event(sendCurrencyReport);
        }
        if (select == "f") {
            queue_event(sendItemsReport);
        }
    }

    return ret_val;
}

bool Menu::check_valid_input(string selection) {
    list<string>::iterator it;
    bool found = false;

    if (valid_actions.front() == "all") {
        return true;
    }

    for( it=valid_actions.begin(); it != valid_actions.end(); it++) {
        if (selection == *it) {
            found = true;
            break;
        }
    }

    return found;
}

void Menu::queue_event(VendingEvent ev, int data, int data1, string s_data1, string s_data2) {
    event_queue.push({ev, data, data1, s_data1, s_data2});
}

EventData Menu::get_menu_event() {
    if (event_queue.empty()) {
        return {noEvent, 0, 0, "", ""};
    }

    EventData front = event_queue.front();
    event_queue.pop();
    return front;
}

void MenuUS::show_coin_menu() {
    valid_actions.clear();

    cout << "Insert coin: " << endl;
    cout << "a) Nickle" << endl;
    cout << "b) Dime" << endl;
    cout << "c) Quarter" <<endl;
    cout << "d) Dollar coin" << endl;
    cout << "e) Done" << endl;

    add_valid_action("a");
    add_valid_action("b");
    add_valid_action("c");
    add_valid_action("d");
    add_valid_action("e");

}

bool MenuUS::do_action(string select) {

    bool ret = Menu::do_action(select);
    if (ret) return ret;

    ret = false;
    if (menuState == addCoin) {
        if (select == "a") { //nickle
            queue_event(coinEvent, 5);
            ret = true;
        }
        if (select == "b") { //dime
            queue_event(coinEvent, 10);
            ret = true;
        }
        if (select == "c") { //quarter
            queue_event(coinEvent, 25);
            ret = true;
        }
        if (select == "d") { //dollar coin
            queue_event(coinEvent, 100);
            ret = true;
        }
        if (select == "e") { //done
            cout << "setting menu state " << endl;
            menuState = mainMenu;
            ret = true;
        }
    }

    if (menuState == selectItem) {
        //this menu object does not understand
        //vending machine inventory nor should it.
        //Send a message to vending machine to handle it.
        queue_event(itemSelectEvent, 0, 0, select);
        menuState = mainMenu;
        ret = true;
    }

    return ret;
}


void MenuUK::show_coin_menu() {
    valid_actions.clear();

    cout << "Insert coin: " << endl;
    cout << "a) 5 Pence" << endl;
    cout << "b) 10 Pence " << endl;
    cout << "c) 20 Pence" <<endl;
    cout << "d) 50 Pence" << endl;
    cout << "e) Pound coin" << endl;
    cout << "f) Done" <<endl;

    add_valid_action("a");
    add_valid_action("b");
    add_valid_action("c");
    add_valid_action("d");
    add_valid_action("e");
    add_valid_action("f");

}

bool MenuUK::do_action(string select) {
    bool ret = Menu::do_action(select);
    if (ret) return ret;

    //coinXMenuEvent can be decoded for denomination from locale context
    ret = false;
    if (menuState == addCoin) {
        if (select == "a") { // 5pence
            queue_event(coinEvent, 5);
            ret = true;
        }
        if (select == "b") { // 10pence
            queue_event(coinEvent, 10);
            ret = true;
        }
        if (select == "c") { // 20pence
            queue_event(coinEvent, 20);
            ret = true;
        }
        if (select == "d") { // 50pence
            queue_event(coinEvent, 50);
            ret = true;
        }
        if (select == "e") { // pound coin
            queue_event(coinEvent, 100);
            ret = true;
        }
        if (select == "f") { // done
            menuState = mainMenu;
            ret = true;
        }
    }

    if (menuState == selectItem) {
        queue_event(itemSelectEvent, 0, 0, select);
        menuState = mainMenu;
        ret = true;
    }
    return ret;
}

Menu* get_menu(string locale) {
    Menu *menu = new MenuUS();

    if (locale.compare("UK") == 0) {
        delete menu;
        menu = new MenuUK();
    }

    return menu;
}