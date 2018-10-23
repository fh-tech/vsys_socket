//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include <sstream>
#include <thread>
#include "include/MailServer.h"

//TODO: starts with ip and port as parameters
int main() {
    MailServer server{"127.0.0.1", 10025};
    server.listen();
}


