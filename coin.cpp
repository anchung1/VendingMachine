//
// Created by Anthony Chung on 9/3/16.
//

#include "coin.h"
#include <iostream>

void Coins::stockCoins(int quantity) {
    for(vector<coin>::iterator it=coins.begin(); it != coins.end(); it++) {
        //not a += because we want to set machine in definitive starting state.
        it->quantity = quantity;
    }
}

void Coins::showCoins() {
    for(vector<coin>::iterator it=coins.begin(); it != coins.end(); it++) {
        cout << it->name << ", " << it->denomination << ", " << it->quantity << endl;
    }
}

bool Coins::operate_by_denomination(int denomination, coinOperation op) {
    bool ret_val = false;
    vector<coin>::iterator it;

    for (it = coins.begin(); it != coins.end(); it++) {
        if (it->denomination == denomination) {
            if (op == coinAdd) {
                it->quantity++;
                ret_val = true;
            }
            if (op == coinRemove) {
                if (it->quantity <= 0) {
                    ret_val = false;
                } else {
                    it->quantity--;
                    ret_val = true;
                }
            }
            if (op == coinQuery) {
                if (it->quantity > 0) {
                    ret_val = true;
                } else {
                    ret_val = false;
                }
            }
            break;
        }
    }
    return ret_val;
}

bool Coins::insertCoin(int denomination) {
    return operate_by_denomination(denomination, coinAdd);
}

bool Coins::removeCoin(int denomination) {
    return operate_by_denomination(denomination, coinRemove);
}

bool Coins::has_fat_coin() {
    return operate_by_denomination(fat_coin_value, coinQuery);
}

void CoinsUS::populate_coins() {
    coins.push_back({"Nickle", 5, 0});
    coins.push_back({"Dime", 10, 0});
    coins.push_back({"Quarter", 25, 0});
    coins.push_back({"Dollar", 100, 0});
    fat_coin_value = 100;
}

void CoinsUK::populate_coins() {
    coins.push_back({"5 Pence", 5, 0});
    coins.push_back({"10 Pence", 10, 0});
    coins.push_back({"20 Pence", 20, 0});
    coins.push_back({"50 Pence", 50, 0});
    coins.push_back({"Pound", 100, 0});
    fat_coin_value = 100;
}


CoinsUS coinsUS = CoinsUS();
CoinsUK coinsUK = CoinsUK();
Coins *get_coins(string locale) {
    if (locale.compare("UK") == 0) {
        return (Coins*)&coinsUK;
    }
    return (Coins*)&coinsUS;
}

