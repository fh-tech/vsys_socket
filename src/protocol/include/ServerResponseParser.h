//
// Created by daniel on 22.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSEPARSER_H
#define VSYS_SOCKET_SERVERRESPONSEPARSER_H

#include <string_view>
#include <variant>
#include <tuple>
#include <charconv>
#include "ServerResponse.h"
#include "ClientRequest.h"

class ServerResponseParser {

public:
    std::variant<ServerResponse, const char*> parse(std::string_view to_parse){
        if (auto result = starts_with("OK\n", to_parse);
            auto remainder = std::get_if<std::string_view>(&result)) {
            return Success{};

        }else if (auto result = starts_with("ERR\n", to_parse);
                auto remainder = std::get_if<std::string_view>(&result)) {
            return Error{};

        }else if (auto result = starts_with("MAIL ", to_parse);
            auto remainder = std::get_if<std::string_view>(&result)) {

            if(auto capture_id_result = match_until("\n", *remainder);
                auto capture_id = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_id_result)) {
                if (auto capture_subject_result = match_until("\n", std::get<1>(*capture_id));
                    auto capture_subject = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_subject_result)) {

                    if (auto capture_to_result = match_until("\n", std::get<1>(*capture_subject));
                            auto capture_to = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_to_result)) {

                        if (auto capture_from_result = match_until("\n", std::get<1>(*capture_to));
                                auto capture_from = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_from_result)) {

                            if (auto capture_payload_result = match_until("\n.\n", std::get<1>(*capture_from));
                                    auto capture_payload = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_payload_result)) {

                                Mail_out mail = {
                                        .id = std::string{std::get<0>(*capture_id)},
                                        .subject = std::string{std::get<0>(*capture_subject)},
                                        .payload = std::string{std::get<0>(*capture_payload)},
                                        .from = std::string{std::get<0>(*capture_from)},
                                        .to = std::string{std::get<0>(*capture_to)},
                                };
                                return mail;
                            }else { return std::get<1>(capture_payload_result); }
                        }else { return std::get<1>(capture_from_result); }
                    }else { return std::get<1>(capture_to_result); }
                }else { return std::get<1>(capture_subject_result); }
            } else { return std::get<1>(capture_id_result); }

        }else if (auto result = starts_with("LIST\n", to_parse);
            auto remainder = std::get_if<std::string_view>(&result)) {
            std::vector<MailDetail> mails{};
            to_parse = *remainder;
            for(
                 auto terminator_result = starts_with(".\n", to_parse);
                 !std::holds_alternative<std::string_view >(terminator_result);
                 terminator_result = starts_with(".\n", to_parse)
            ){
                if (auto capture_id_result = match_until(" ", to_parse);
                    auto capture_id = std::get_if<std::tuple<std::string_view, std::string_view>>(&capture_id_result)){
                    if (auto capture_subject_result = match_until("\n", std::get<1>(*capture_id));
                        auto capture_subject = std::get_if<std::tuple<std::string_view, std::string_view>>(&capture_subject_result)){
                        to_parse = std::get<1>(*capture_subject);
                        mails.emplace_back(MailDetail{
                                std::string{std::get<0>(*capture_id)},
                                std::string{std::get<0>(*capture_subject)}
                        });
                    } else{ return std::get<1>(capture_subject_result); }
                }else{ return std::get<1>(capture_id_result); }
            }
            return Mail_list{
                .mail_out = mails
            };
        }

        return "ERR";
    }


private:
    std::variant<std::string_view, const char*> starts_with(const char start, const std::string_view to_parse){
        if(to_parse.length() >= 1) {
            if(to_parse[0] == start){
                return to_parse.substr(1, to_parse.length());
            }else{
                return "ERR";
            }
        }else{
            return "incomplete";
        }
    }

    std::variant<std::string_view, const char*> starts_with(const std::string_view start, const std::string_view to_parse){
        if(to_parse.length() >= start.length()){
            if(to_parse.find(start, 0) == 0){
                return to_parse.substr(start.length(), to_parse.length());
            } else {
                return "ERR";
            }
        } else {
            return "incomplete";
        }
    }

    std::variant<std::tuple<std::string_view, std::string_view>, const char*> match_until(const char* until, std::string_view to_parse){
        if(to_parse.length() > 1){
            auto until_pos = to_parse.find(until);
            if(until_pos > 0 && until_pos != std::string_view::npos) {
                if(until_pos + 1 == to_parse.length()){
                    return std::make_tuple<>(to_parse.substr(0, until_pos), "");
                }else {
                    return std::make_tuple<>(to_parse.substr(0, until_pos),
                                             to_parse.substr(until_pos + 1, to_parse.length()));
                }
            } else {
                return "incomplete";
            }
        } else {
            return "incomplete";
        }
    }

};

#endif //VSYS_SOCKET_SERVERRESPONSEPARSER_H
