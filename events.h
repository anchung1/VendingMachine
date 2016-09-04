//
// Created by Anthony Chung on 9/3/16.
//

#ifndef VENDME_EVENTS_H
#define VENDME_EVENTS_H

#include <string>
using namespace std;

enum VendingEvent { noEvent, refundMenuEvent,
    coinEvent, creditEvent, billEvent, ejectCoinEvent,
    quitMenuEvent
};


typedef struct EventData_ {
    VendingEvent type;
    int data;
} EventData;

extern string translate_event(EventData ev);

#endif //VENDME_EVENTS_H
