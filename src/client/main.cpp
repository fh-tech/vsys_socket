//
// Created by viktorl on 28.09.18.
//


#include <iostream>
#include "../shared/Clientsocket.h"

int main() {
    ClientSocket csocket = ClientSocket();
    Socket s = csocket.connect_to(10025, "0.0.0.0");
    std::cout << s.receive() << std::endl;
    return 0;
}