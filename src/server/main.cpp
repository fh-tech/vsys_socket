//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include <sstream>
#include <thread>
#include <socket-lib/include/include.h>
#include "MailServer.h"

int main() {
    MailServer server{"127.0.0.1", 8088
    };
    server.listen();
}


