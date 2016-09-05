# VendingMachine
# To build on Apple Mac Terminal do:

g++ -std=c++11 main.cpp chocolate.cpp coin.cpp events.cpp menu.cpp simulation.cpp VendingMachine.cpp

Run it like this:
./a.out US   or ./a.out UK
The argument specifies US or UK locale.  US is default.

Big Picture:

Simulator spawns Menu and Vending Machine objects.

The logic flow is one direction:
Menu == input q ==> Vending Machine == output q ==> output devices

Menu simulates input devices including keyboard item selector, coin/bill/credit input devices.
Menu sends event messages to the input Q to communicate with the Vending Machine.

Vending Machine emits an event to the output Q in response to input event messages.
The simulator prints the event messages since output devices are not simulated.

Presumably all input/output devices are connected to the Vending Machine via serial port.

chocolate.cpp models inventory in the vending machine.
coin.cpp models two different currencies (US, UK).



