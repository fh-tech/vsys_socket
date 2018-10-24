//
// Created by viktorl on 24.10.18.
//

#include "include/UserServerResponsePrinter.h"

void UserServerResponsePrinter::operator()(const Error &l) {
    os << "Something went wrong." << std::endl;
}

void UserServerResponsePrinter::operator()(Success const &l) {
    os << "Success" << std::endl;
}

void UserServerResponsePrinter::operator()(Mail_list const &l) {
    os << "Number of messages: " << l.mail_out.size() << std::endl;

    for(int i = 0; i < l.mail_out.size(); i++) {
        os << "(" << i << ") " << l.mail_out.at(i).subject << std::endl;
    }
}

void UserServerResponsePrinter::operator()(Mail_out const &l) {
    os << "Subject: " << l.subject << std::endl;
    os << "From: " << l.from << std::endl;
    os << "To: " << l.to << std::endl;
    os << "Payload: " << l.payload << std::endl;
}

