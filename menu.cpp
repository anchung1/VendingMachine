//
// Created by Anthony Chung on 9/3/16.
//

#include "menu.h"

void Menu::show_main_menu() {
    valid_actions.clear();

    cout << "Select an action: " << endl;
    cout << "a) Add Coin" << endl;
    cout << "b) Select Item" << endl;
    cout << "c) Refund" << endl;
    cout << "d) Quit" << endl;
    cout << "Enter 'a', 'b', 'c' or 'd': " << endl;

    add_valid_action('a');
    add_valid_action('b');
    add_valid_action('c');
    add_valid_action('d');
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

void Menu::add_valid_action(char input) {
    valid_actions.push_back(input);
    valid_actions.push_back((char)toupper(input));
}

void Menu::get_menu_selection() {
    char selection;
    cin >> selection;

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

bool Menu::do_action(char select) {
    bool ret_val = false;

    if (menuState == mainMenu) {
        ret_val = true;
        switch (select) {
            case 'a':
                menuState = addCoin;
                break;
            case 'b':
                menuState = selectItem;
                break;
            case 'c':
                queue_event(refundMenuEvent, 0);
                break;
            case 'd':
                queue_event(quitMenuEvent, 0);
                break;
            default:
                break;
        }
    }

    return ret_val;
}

bool Menu::check_valid_input(char selection) {
    vector<char>::iterator it;
    bool found = false;

    for( it=valid_actions.begin(); it != valid_actions.end(); it++) {
        if (selection == *it) {
            found = true;
            break;
        }
    }

    return found;
}

void Menu::queue_event(VendingEvent ev, int data) {

    event_queue.push({ev, data});
}

EventData Menu::get_menu_event() {
    if (event_queue.empty()) {
        return {noEvent, 0};
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

    add_valid_action('a');
    add_valid_action('b');
    add_valid_action('c');
    add_valid_action('d');
    add_valid_action('e');

}

bool MenuUS::do_action(char select) {

    bool ret = Menu::do_action(select);
    if (ret) return ret;

    ret = true;
    if (menuState == addCoin) {
        switch (select) {
            case 'a': //nickle
                queue_event(coinEvent, 5);
                break;
            case 'b': //dime
                queue_event(coinEvent, 10);
                break;
            case 'c': //quarter
                queue_event(coinEvent, 25);
                break;
            case 'd': //dollar coin
                queue_event(coinEvent, 100);
                break;
            case 'e': //done
                cout << "setting menu state " << endl;
                menuState = mainMenu;
                break;
            default:
                ret = false;
                break;
        }
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

    add_valid_action('a');
    add_valid_action('b');
    add_valid_action('c');
    add_valid_action('d');
    add_valid_action('e');
    add_valid_action('f');

}

bool MenuUK::do_action(char select) {
    bool ret = Menu::do_action(select);
    if (ret) return ret;

    //coinXMenuEvent can be decoded for denomination from locale context
    ret = true;
    if (menuState == addCoin) {
        switch (select) {
            case 'a': // 5pence
                queue_event(coinEvent, 5);
                break;
            case 'b': // 10pence
                queue_event(coinEvent, 10);
                break;
            case 'c': // 20pence
                queue_event(coinEvent, 20);
                break;
            case 'd': // 50pence
                queue_event(coinEvent, 50);
                break;
            case 'e': // pound coin
                queue_event(coinEvent, 100);
                break;
            case 'f': //done
                menuState = mainMenu;
                break;
            default:
                ret = false;
                break;
        }
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