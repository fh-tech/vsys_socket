//
// Created by viktorl on 28.09.18.
//


#include <sstream>
#include <Clientsocket.h>
#include <ClientRequest.h>
#include <ClientRequestPrinter.h>
#include <ServerResponse.h>
#include <ServerResponseParser.h>
#include "include/Client.h"


//TODO: started with ip and port as params
int main() {
    Client client(10025, "127.0.0.1");
    client.start();
}




