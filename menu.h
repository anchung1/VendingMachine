//
// Created by Anthony Chung on 9/3/16.
//

#ifndef VENDME_MENU_H
#define VENDME_MENU_H

#include <iostream>
#include <vector>
#include <queue>
#include "events.h"

using namespace std;

enum MenuState { mainMenu, addCoin, selectItem };

class Menu {

protected:
    vector<char> valid_actions;
    queue<EventData> event_queue;

    MenuState menuState;

    void add_valid_action(char input);
    bool check_valid_input(char selection);
    Menu() { menuState = mainMenu; }

    void queue_event(VendingEvent ev, int data);

public:
    virtual ~Menu() {
        valid_actions.clear();
    };

    void show_main_menu();
    void get_menu_selection();
    void show_menu();
    void show_item_menu() {
        cout << "Under construction. " << endl;
    };
    virtual bool do_action(char select);
    virtual void show_coin_menu() {};

    EventData get_menu_event();

};

class MenuUS: public Menu {

public:
    MenuUS() : Menu() {
        cout << "US Menu" << endl;
    }
    ~MenuUS() {
        cout << "US Menu remove" << endl;
    }

    void show_coin_menu();
    bool do_action(char select);

};


class MenuUK: public Menu {
public:
    MenuUK() : Menu() {
        cout << "UK Menu" << endl;
    }
    ~MenuUK() {
        cout << "UK Menu remove" << endl;
    }
    void show_coin_menu();
    bool do_action(char select);
};

extern Menu* get_menu(string locale);
#endif //VENDME_MENU_H
