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
            << "\n"
            << "Choose option:\n"
            << "(1) LOGIN\n"
            << "(q) QUIT\n" << std::endl;
}

void Client::showOptions_postLogin() const {
    std::cout
            << "\n"
            << "Choose option:\n"
            << "(2) SEND\n"
            << "(3) LIST\n"
            << "(4) READ\n"
            << "(5) DEL\n"
            << "(q) QUIT\n" << std::endl;
}

char Client::getOption() const {
    std::string line;
    char input{};
    while (true) {
        std::cout << ": " << std::flush;
        std::cin >> input;
        // to discard characters after the input we read
        std::cin.ignore();
        std::tuple range = this->loggedIn ? std::make_tuple('2', '5') : std::make_tuple('1', '1');
        if ((input >= std::get<0>(range) && input <= std::get<1>(range)) || input == 'q') {
            break;
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
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            break;
        }

        case '3': {
            ClientRequest cr = this->buildListRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            this->handleListResponse(response);
            break;
        }

        case '4': {
            ClientRequest cr = this->buildReadRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            break;
        }

        case '5': {
            ClientRequest cr = this->buildDeleteRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            break;
        }
        case 'q': {
            ClientRequest cr = this->buildQuitRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
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
    std::string to;
    std::cout << "Recipient: " << std::flush;
    std::getline(std::cin, to);

    std::string subject;
    std::cout << "Subject: " << std::endl;
    std::getline(std::cin, subject);

    std::cout << "Write Msg: (ends with \\n.\\n)" << std::endl;

    std::string msg;
    std::string tmp;

    while (tmp != ".\n") {
        std::getline(std::cin, tmp);
        tmp.push_back('\n');
        msg += tmp;
    }

    msg.pop_back();
    msg.pop_back();

    return Send{
            .to = to,
            .subject = subject,
            .msg = msg,
    };
}

List Client::buildListRequest() const {
    return List();
}

Delete Client::buildDeleteRequest() const {
    std::string input;
    std::cout << "Please enter which message you want to delete: " << std::flush;
    std::cin >> input;
    auto id = static_cast<msg_id>(std::stol(input));
    return Delete{.id = id};
}

Quit Client::buildQuitRequest() const {
    return Quit();
}

Read Client::buildReadRequest() const {
    std::string input;
    std::cout << "Please enter which message you want to read: " << std::flush;
    std::cin >> input;
    auto id = static_cast<msg_id>(std::stol(input));
    return Read{.id = id};
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

void Client::handleListResponse(ServerResponse response) {
    if (auto list = std::get_if<Mail_list>(&response)) {
        this->inbox = list->mail_out;
    }
}


