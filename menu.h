//
// Created by Anthony Chung on 9/3/16.
//

#ifndef VENDME_MENU_H
#define VENDME_MENU_H

#include <iostream>
#include <list>
#include <queue>
#include "events.h"

using namespace std;

enum MenuState { mainMenu, addCoin, selectItem };

class Menu {

protected:
    list<string> valid_actions;

    queue<EventData> event_queue;
    MenuState menuState;

    void add_valid_action(string input);
    bool check_valid_input(string selection);
    Menu() { menuState = mainMenu; }

    void queue_event(VendingEvent ev, int data=0, int data1=0, string s_data1="", string s_data2="");

public:
    virtual ~Menu() {
        valid_actions.clear();
    };

    void show_main_menu();
    void get_menu_selection();
    void show_menu();
    void show_item_menu();
    virtual bool do_action(string select);
    virtual void show_coin_menu() {};

    EventData get_menu_event();

};

class MenuUS: public Menu {

public:
    MenuUS() : Menu() {};
    ~MenuUS() {};

    void show_coin_menu();
    bool do_action(string select);

};


class MenuUK: public Menu {
public:
    MenuUK() : Menu() {};
    ~MenuUK() {};

    void show_coin_menu();
    bool do_action(string select);
};

extern Menu* get_menu(string locale);
#endif //VENDME_MENU_H
