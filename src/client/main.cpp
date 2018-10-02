//
// Created by viktorl on 28.09.18.
//


#include "../shared/include/include.h"

int main() {
    ClientSocket csocket = ClientSocket();
    Socket s = csocket.connect_to(10025, "0.0.0.0");
    std::cout << s.receive() << std::endl;
    sleep(1);
    std::string longMessage = "This message has to be sent over multiple messages i am sure about that that must at least be read over alot of messages if i read 10chars at once";
    s.send_msg(longMessage);



    return 0;
}