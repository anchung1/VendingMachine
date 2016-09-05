//
// Created by Anthony Chung on 9/3/16.
//

#include "events.h"
#include <iostream>
using namespace std;

string eventString[] = {
                        "noEvent", "refundMenuEvent", "coinEvent",
                        "creditEvent", "billEvent", "ejectCoinEvent",
                        "showFundsEvent",
                        "itemSelectEvent", "itemDispenseEvent","itemDataRequestEvent", "itemDataReportEvent",
                        "sendCurrencyReport", "sendItemsReport",
                        "quitMenuEvent"
                        };


string translate_event(EventData& ev) {
    string msg = "";

    msg = "event: " + eventString[(int)ev.type] + " data: " + to_string(ev.data);
    return msg;
}
