//
// Created by viktorl on 23.10.18.
//

#include "include/Client.h"


Client::Client(uint16_t port, const std::string &ip) : loggedIn(false) {
    ClientSocket cs{};
    this->socket = cs.connect_to(port, ip);
}

void Client::start() {
    while (!loggedIn) {
        showOptions_preLogin();
        int option = getOption(1, 2);
        if (option == 2) exit(0);

        // only other option
        ClientRequest cr = buildLoginRequest();
        std::stringstream ss{};
        std::visit(ClientRequestPrinter{ss}, cr);
        // send request
        this->socket->send_msg(ss.str());
        // get response
        auto response = this->get_Response();
        if (auto res = std::get_if<ServerResponse>(&response)) {
            if (std::holds_alternative<Success>(*res)) {
                this->loggedIn = true;
            } else {
                std::cout << "Login failed." << std::endl;
            }
        } else {
            std::cout << "Login failed." << std::endl;
        }
    }

    while (1) {
        showOptions_postLogin();
        int option = getOption(1, 5);
        if (option == 5) break;
        ClientRequest cr = handleOption(option);
        std::stringstream ss{};
        std::visit(ClientRequestPrinter{ss}, cr);
        this->socket->send_msg(ss.str());
    }
}


std::variant<ServerResponse, const char *> Client::get_Response() {
    ServerResponseParser parser{};
    std::string msg;
    std::variant<ServerResponse, const char *> result;
    do {
        msg += this->socket->read_line();
        result = parser.parse(msg);
    } while (std::holds_alternative<const char *>(result) && !strcmp(std::get<const char *>(result), "incomplete"));
    return result;
}


void Client::showOptions_preLogin() {
    std::cout
            << "Choose option:\n"
            << "(1) LOGIN\n"
            << "(2) QUIT\n" << std::endl;
}

void Client::showOptions_postLogin() {
    std::cout
            << "Choose option:\n"
            << "(1) SEND\n"
            << "(2) LIST\n"
            << "(3) READ\n"
            << "(4) DEL\n"
            << "(5) QUIT\n"
    << std::endl;
}

int Client::getOption(int min, int max) {
    std::string line;
    int input;
    while (true) {
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

ClientRequest Client::handleOption(int option) {
    ClientRequest cr;
    switch (option) {
        case 1:
            cr = this->buildSendRequest();
            break;
        case 2:
            cr = this->buildListRequest();
            break;
        case 3:
            cr = this->buildReadRequest();
            break;
        case 4:
            cr = this->buildDeleteRequest();
            break;
        case 5:
            cr = this->buildQuitRequest();
        default:
            std::cout << "Something went wrong here" << std::endl;
    }
    return cr;
}

Send Client::buildSendRequest() {
    std::string to;
    std::cout << "Recipient: " << std::flush;
    std::cin >> to;
    std::string subject;
    std::cout << "Subject: " << std::endl;
    std::cin >> subject;

    std::cout << "Write Msg: (ends with \\n.\\n)" << std::endl;
    std::string msg;
    std::string tmp;

    while (tmp != ".") {
        std::cin >> tmp;
        msg += tmp;
    }

    msg.pop_back();

    return Send{
            .to = to,
            .subject = subject,
            .msg = msg,
    };
}

List Client::buildListRequest() {
    return List();
}

Delete Client::buildDeleteRequest() {
    return Delete();
}

Quit Client::buildQuitRequest() {
    return Quit();
}

Read Client::buildReadRequest() {
    return Read();
}

Login Client::buildLoginRequest() {
    std::string username = this->getUsername();
    std::string password{};
    std::cout << "Password: ";
    std::cin >> password;
    return Login{.username = username, .password = password};
}

std::string Client::getUsername() {
    std::string line{};
    while (line.empty() || line.size() > 8) {
        std::cout << "Username: ";
        std::getline(std::cin, line);
        if (line.size() > 8) std::cout << "Invalid Input" << std::endl;
    }
    return line;
}




