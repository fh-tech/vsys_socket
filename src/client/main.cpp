//
// Created by viktorl on 28.09.18.
//


#include <sstream>
#include "../shared/socket/Clientsocket.h"
#include "../shared/socket/Socket.h"

int main() {
    char buf[256];
    ClientSocket csocket = ClientSocket();

    Socket s = csocket.connect_to(10025, "0.0.0.0");
    while (s) {
        try {
            s.receive(buf, 10);
        } catch(std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        int i;
        std::stringstream{buf} >> i;
        i++;
        std::cout << i << std::endl;
        std::string reply = std::to_string(i);
        s.send_msg(reply);
    }
    return 0;
}