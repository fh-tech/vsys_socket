//
// Created by viktorl on 23.10.18.
//

#include <optional>
#include "include/Client.h"
#include "include/UserServerResponsePrinter.h"

Client::Client(uint16_t port, const std::string &ip) : loggedIn(false) {
    ClientSocket cs{};
    this->socket = cs.connect_to(port, ip);
}

void Client::start() {
    try {
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
    } catch(std::runtime_error &e) {
        std::cout << "Server terminated your session. You probably have been banned." << std::endl;
        exit(0);
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
            std::visit(UserServerResponsePrinter(std::cout), response);
            break;
        }
        case '2': {
            ClientRequest cr = this->buildSendRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            this->handleSendResponse(response);
            std::visit(UserServerResponsePrinter(std::cout), response);
            break;
        }
        case '3': {
            ClientRequest cr = this->buildListRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            this->handleListResponse(response);
            std::visit(UserServerResponsePrinter(std::cout), response);
            break;
        }
        case '4': {
            // client side validation (check inbox)
            std::optional<ClientRequest> cr = this->buildReadRequest();
            if (cr) {
                this->socket->send_msg(getRequestString(cr.value()));
                response = this->get_Response();
                std::visit(UserServerResponsePrinter(std::cout), response);
            }
            break;
        }
        case '5': {
            // client side validation (check inbox)
            std::optional<ClientRequest> cr = this->buildDeleteRequest();
            if (cr) {
                this->socket->send_msg(getRequestString(cr.value()));
                response = this->get_Response();
                this->handleDeleteResponse(response, cr.value());
                std::visit(UserServerResponsePrinter(std::cout), response);
            }
            break;
        }
        case 'q': {
            ClientRequest cr = this->buildQuitRequest();
            this->socket->send_msg(getRequestString(cr));
            response = this->get_Response();
            std::visit(UserServerResponsePrinter(std::cout), response);
            break;
        }
        default:
            std::cout << "Something went wrong here." << std::endl;
    }
}


void Client::updateInbox() {
    ClientRequest cr = this->buildListRequest();
    this->socket->send_msg(getRequestString(cr));
    ServerResponse response = this->get_Response();
    this->handleListResponse(response);
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

std::optional<Delete> Client::buildDeleteRequest() const {
    this->listInbox();
    if (this->inbox.empty()) {
        std::cout << "There are no messages to delete - maybe try to poll the server for new messages." << std::endl;
        return std::nullopt;
    } else {
        std::cout << "Please enter which message you want to delete" << std::flush;
        auto id = getValidID();
        return Delete{.id = id};
    }
}

std::optional<Read> Client::buildReadRequest() const {
    this->listInbox();
    if (this->inbox.empty()) {
        std::cout << "You have no messages to read - maybe try to poll the server for new messages." << std::endl;
        return std::nullopt;
    } else {
        std::cout << "Please enter which message you want to read: " << std::flush;
        auto id = getValidID();
        return Read{.id = id};
    }
}

msg_id Client::getValidID() const {
    std::string input;
    bool valid = false;
    do {
        std::cout << ": ";
        std::cin >> input;
        for (MailDetail md : inbox) {
            if (md.id == input) {
                valid = true;
                break;
            }
        }
        if (!valid) std::cout << "Invalid Input." << std::endl;
    } while (!valid);
    return static_cast<msg_id>(std::stol(input));
}

Quit Client::buildQuitRequest() const {
    return Quit();
}

Login Client::buildLoginRequest() const {
    std::string username = this->getUsername();
    std::string password = this->getpass("Password: ", true);
//    std::cout << "Password: ";
//    std::cin >> password;
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

int Client::getch() const {
    int ch;
    struct termios t_old{}, t_new{};
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

std::string Client::getpass(const char *prompt, bool show_asterisk = true) const {
    const char BACKSPACE = 127;
    const char RETURN = 10;

    std::string password;
    unsigned char ch = 0;

    std::cout << prompt << std::endl;

    while ((ch = getch()) != RETURN) {
        if (ch == BACKSPACE) {
            if (password.length() != 0) {
                if (show_asterisk)
                    std::cout << "\b \b";
                password.resize(password.length() - 1);
            }
        } else {
            password += ch;
            if (show_asterisk)
                std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

void Client::handleLoginResponse(ServerResponse response) {
    if (std::holds_alternative<Success>(response)) {
        this->loggedIn = true;
        this->handleRequest('3');
    } else {
        std::cout << "Login failed." << std::endl;
    }
}

void Client::handleListResponse(ServerResponse response) {
    if (auto list = std::get_if<Mail_list>(&response)) {
        this->inbox = list->mail_out;
    }
}

void Client::handleDeleteResponse(ServerResponse response, ClientRequest &clientRequest) {
    if (auto req = std::get_if<Delete>(&clientRequest)) {
        if (auto del = std::get_if<Success>(&response)) {
            for (auto it = this->inbox.begin(); it != this->inbox.end(); it++) {
                if (it->id == std::to_string(req->id)) {
                    this->inbox.erase(it);
                    break;
                }
            }
        }
    } else {
        // if deleting from inbox cant be done fetch from server
        updateInbox();
    }
}

void Client::handleSendResponse(ServerResponse response) {
    // if sending was success automatically update the inbox
    if (auto send = std::get_if<Success>(&response)) {
        this->updateInbox();
    }
}

void Client::listInbox() const {
    std::cout << "============ Inbox (send List to update) =============" << std::endl;
    if (!inbox.empty()) {
        for (auto const &mail: inbox) {
            std::cout << "[ " << mail.id << " ]" << "\t" << mail.subject << std::endl;
        }
        std::cout << std::endl;
    } else {
        std::cout << " No messages." << std::endl;
    }
}





