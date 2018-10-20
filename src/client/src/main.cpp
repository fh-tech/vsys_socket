//
// Created by viktorl on 28.09.18.
//


#include <sstream>
#include <Clientsocket.h>
#include <ClientRequest.h>
#include <ClientRequestPrinter.h>

void showOptions_preLogin();
void showOptions_postLogin();
int getOption(int min, int max);
ClientRequest handleOption(int option);
Send buildSendRequest();
List buildListRequest();
Read buildReadRequest();
Delete buildDeleteRequest();
Quit buildQuitRequest();
Login buildLoginRequest();
std::string getUsername();
//will be implemented in part2
//buildLoginRequest();

int main() {
    char buf[256];
    ClientSocket csocket = ClientSocket();
    Socket s = csocket.connect_to(10025, "0.0.0.0");

    bool loggedIn = false;
    // only login or quit
    while(!loggedIn) {
        showOptions_preLogin();
        int option = getOption(1,2);
        if(option == 2) exit(0);
        ClientRequest cr = buildLoginRequest();
        std::stringstream ss{};
//        std::visit(ClientRequestPrinter{ss}, cr);
//        std::cout << ss.str() << std::endl;
        s.send_msg(ss.str());
        std::string line = s.read_line();
        do {
           line = s.read_line();
           std::cout << line;
        } while(!line.empty());
    }

//    while (s) {
//        showOptions();
//        int option = getOption();
//        if(option == 5) break;
//        ClientRequest cr = handleOption(option);
//        s.send_msg(cr);
//    }
    return 0;
}


void showOptions_postLogin() {
    std::cout
        << "Choose option:\n"
        << "(1) SEND\n"
        << "(2) LIST\n"
        << "(3) READ\n"
        << "(4) DEL\n"
        << "(5) QUIT\n" << std::endl;
}

void showOptions_preLogin() {
    std::cout
        << "Choose option:\n"
        << "(1) LOGIN\n"
        << "(2) QUIT\n" << std::endl;
}

//min max inclusive!
int getOption(int min, int max) {
    std::string line;
    int input;
    while (1) {
        std::cout << ": ";
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (ss >> input) {
            if (ss.eof() && input >= min && input <= max) {   // Success
                break;
            }
        }
        std::cout << "Invalid Input" << std::endl;
    }
    return input;
}

ClientRequest handleOption(int option) {
    ClientRequest cr{};
    switch(option) {
        case 1:
            cr = buildSendRequest();
            break;
        case 2:
            cr = buildListRequest();
            break;
        case 3:
            cr = buildReadRequest();
            break;
        case 4:
            cr = buildDeleteRequest();
            break;
        case 5:
            cr = buildQuitRequest();
        default:
            std::cout << "Something went wrong here" << std::endl;
    }
}

Send buildSendRequest() {}
List buildListRequest() {}
Read buildReadRequest() {}
Delete buildDeleteRequest() {}
Quit buildQuitRequest() {};

Login buildLoginRequest() {
    std::string username = getUsername();
    std::string password{};
    std::cout << "Password: ";
    std::cin >> password;
    return Login {.username = username, .password = password};
}

std::string getUsername() {
    std::string line{};
    while (line.empty() || line.size() > 8) {
        std::cout << "Username: ";
        std::getline(std::cin, line);
        if(line.size() > 8) std::cout << "Invalid Input" << std::endl;
    }
    return line;
}