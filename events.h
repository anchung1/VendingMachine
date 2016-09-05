//
// Created by Anthony Chung on 9/3/16.
//

#ifndef VENDME_EVENTS_H
#define VENDME_EVENTS_H

#include <string>
using namespace std;

enum VendingEvent { noEvent, refundMenuEvent,
    coinEvent, creditEvent, billEvent, ejectCoinEvent, showFundsEvent,
    itemSelectEvent, itemDispenseEvent,itemDataRequestEvent, itemDataReportEvent,
    sendCurrencyReport, sendItemsReport, quitMenuEvent
};


typedef struct EventData_ {
    VendingEvent type;
    int data;
    int data2;
    string s_data1;
    string s_data2;
} EventData;

extern string translate_event(EventData& ev);

#endif //VENDME_EVENTS_H
