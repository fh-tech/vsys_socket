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

void UserServerResponsePrinter::operator()(Mail_list const &list) {

    os << "============ Inbox =============" << std::endl;
    if(!list.mail_out.empty()){
        for(auto const& mail: list.mail_out){
            os << "[ " << mail.id << " ]" << "\t" << mail.subject << std::endl;
        }
        os << std::endl;
    } else {
        os << "No messages." << std::endl;
    }
}

void UserServerResponsePrinter::operator()(Mail_out const &l) {
    os << "Subject: " << l.subject << std::endl;
    os << "From: " << l.from << std::endl;
    os << "To: " << l.to << std::endl;
    os << "Payload: " << l.payload << std::endl;
}

