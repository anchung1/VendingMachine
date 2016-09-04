#include <iostream>
#include "main.h"

using namespace std;

int main(int argc, char **argv) {

    string locale = "US";
    if (argc >= 2) {
        //user input check done by simulator
        locale = argv[1];
    }

    Simulation simulation;
    simulation.set_localization(locale);
    simulation.simulate();

    return 0;
}


