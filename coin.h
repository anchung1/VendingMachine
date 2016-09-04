//
// Created by Anthony Chung on 9/3/16.
//

#ifndef VENDME_COIN_H
#define VENDME_COIN_H

#include <string>
#include <vector>
#include "events.h"
using namespace std;

//British coins
//5pence, 10pence, 20pence, 50pence, 1pound

//US coins
//5cents, 10cents, 25cents, 1dollar

enum coinOperation {coinAdd, coinRemove, coinQuery};

typedef struct coin_ {
    string name;
    int denomination;
    int quantity;
} coin;

class Coins {
protected:
    vector<coin> coins;
    Coins() {};
    int fat_coin_value; //coin value equivalent of "dollar" bill
    virtual void populate_coins() {};

    bool operate_by_denomination(int denomination, coinOperation op);

public:
    virtual ~Coins() { coins.clear(); }
    void stockCoins(int quantity);
    void showCoins();

    bool insertCoin(int denomination);
    bool removeCoin(int denomination);

    bool has_fat_coin();
    int get_fat_coin_value() {return fat_coin_value;}
};

class CoinsUS : public Coins {

    void populate_coins();

public:
    CoinsUS() : Coins() {
        populate_coins();
    }
};

class CoinsUK : public Coins {
    void populate_coins();
public:
    CoinsUK() : Coins() {
        populate_coins();
    }
};

extern int get_denomination(string locale);
extern Coins* get_coins(string locale);
#endif //VENDME_COIN_H
