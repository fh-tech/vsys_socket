//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include "../shared/include/include.h"

int main() {
    Serversocket ssocket = Serversocket("0.0.0.0", 10025, 5);

    while(Socket s = ssocket.listen_accept()){

        std::string message = "Welcome to your mail server";
        s.send_msg(message);
        sleep(1);
        std::cout << s.receive() << std::endl;
    }

    return 0;
}