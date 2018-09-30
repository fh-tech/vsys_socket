//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include "../shared/Serversocket.h"

int main() {
    Serversocket ssocket = Serversocket("0.0.0.0", 10025, 5);
    Socket s = ssocket.listen_accept();
    std::string message = "Welcome to your mail server";
    s.send_msg(message);
    return 0;
}