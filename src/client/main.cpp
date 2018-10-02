//
// Created by viktorl on 28.09.18.
//


#include <sstream>
#include "../shared/include/include.h"

int main() {
    ClientSocket csocket = ClientSocket();

    Socket s = csocket.connect_to(10025, "0.0.0.0");
    while (s) {
        std::string msg = s.receive();
        int i;
        std::stringstream{msg} >> i;
        i++;
        std::cout << i << std::endl;
        std::string reply = i + "";
        s.send_msg(reply);
    }
    return 0;
}