//
// Created by viktorl on 23.10.18.
//

#include "include/Client.h"
#include "include/UserServerResponsePrinter.h"

Client::Client(uint16_t port, const std::string &ip) : loggedIn(false) {
    ClientSocket cs{};
    this->socket = cs.connect_to(port, ip);
}

void Client::start() {
    while (!loggedIn) {
        showOptions_preLogin();
        char option = getOption();
        handleRequest(option);
        if (option == 'q') exit(0);
    }

    while (true) {
        showOptions_postLogin();
        char option = getOption();
        handleRequest(option);
        if (option == 'q') exit(0);
    }
}


ServerResponse Client::get_Response() const {
    ServerResponseParser parser{};
    std::string msg;
    std::variant < ServerResponse,
    const char*> result;
    do {
        msg += this->socket->read_line();
        result = parser.parse(msg);
    } while (std::holds_alternative<const char *>(result) && !strcmp(std::get<const char *>(result), "incomplete"));
    if (auto response = std::get_if<ServerResponse>(&result)) {
        return *response;
    } else {
        return Error();
    }
}


void Client::showOptions_preLogin() const {
    std::cout
            << "Choose option:\n"
            << "(1) LOGIN\n"
            << "(q) QUIT\n" << std::endl;
}

void Client::showOptions_postLogin() const {
    std::cout
            << "Choose option:\n"
            << "(2) SEND\n"
            << "(3) LIST\n"
            << "(4) READ\n"
            << "(5) DEL\n"
            << "(q) QUIT\n" << std::endl;
}

char Client::getOption() const {
    std::string line;
    char input;
    while (true) {
        std::cout << ": " << std::flush;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (ss >> input) {
            std::tuple range = this->loggedIn ? std::make_tuple('2', '5') : std::make_tuple('1', '5');
            if ((input >= std::get<0>(range) && input <= std::get<1>(range)) || input == 'q') {
                break;
            }
        }
        std::cout << "Invalid Input" << std::endl;
    }
    return input;
}

// 1. builds a request
// 2. sends it
// 3. receives response
// 4. parses it
// 5. sends it to the handle
// 6. prints it
void Client::handleRequest(char option) {
    ServerResponse response;
    switch (option) {
        case '1': {
            ClientRequest cr = this->buildLoginRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            this->handleLoginResponse(response);
            break;
        }
        case '2': {
            ClientRequest cr = this->buildSendRequest();
            break;
        }

        case '3': {
            ClientRequest cr = this->buildListRequest();
            break;
        }

        case '4': {
            ClientRequest cr = this->buildReadRequest();
            break;
        }

        case '5': {
            ClientRequest cr = this->buildDeleteRequest();
            break;
        }

        case 'q': {
            ClientRequest cr = this->buildQuitRequest();
            break;
        }
        default:
            std::cout << "Something went wrong here." << std::endl;
    }
    // now every response gets printed to the user
    std::visit(UserServerResponsePrinter(std::cout), response);
}

std::string Client::getRequestString(ClientRequest &cr) const {
    std::stringstream ss{};
    std::visit(ClientRequestPrinter{ss}, cr);
    return ss.str();
}

Send Client::buildSendRequest() const {
    return Send();
}

List Client::buildListRequest() const {
    return List();
}

Delete Client::buildDeleteRequest() const {
    std::string input;
    std::cout << "Please enter which message you want to delete: " << std::flush;
    std::cin >> input;
    return {};
}

Quit Client::buildQuitRequest() const {
    return Quit();
}

Read Client::buildReadRequest() const {
    return Read();
}

Login Client::buildLoginRequest() const {
    std::string username = this->getUsername();
    std::string password{};
    std::cout << "Password: ";
    std::cin >> password;
    return Login{.username = username, .password = password};
}

std::string Client::getUsername() const {
    std::string line{};
    while (line.empty() || line.size() > 8) {
        std::cout << "Username: ";
        std::getline(std::cin, line);
        if (line.size() > 8) std::cout << "Invalid Input" << std::endl;
    }
    return line;
}

void Client::handleLoginResponse(ServerResponse response) {
    if (std::holds_alternative<Success>(response)) {
        this->loggedIn = true;
    } else {
        std::cout << "Login failed." << std::endl;
    }
}



