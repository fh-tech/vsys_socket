//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include <sstream>
#include <thread>
#include "../shared/include/include.h"

void handle_client(Socket& s){
    char buf[256];
    std::string msg = "0";
    s.send_msg(msg);

    while (s){
        int i;
        s.receive(buf, 10);
        std::stringstream{buf} >> i;
        i++;
        std::string outg = std::to_string(i);
        std::cout << i << std::endl;
        s.send_msg(outg);
    }
}

int main() {
    Serversocket ssocket = Serversocket("0.0.0.0", 10025, 5);
    while(Socket s = ssocket.listen_accept()){

        handle_client(s);
        sleep(1);
    }

    return 0;
}


