//
// Created by daniel on 05.10.18.
//

#ifndef VSYS_SOCKET_CLIENTREQUESTPARSER_H
#define VSYS_SOCKET_CLIENTREQUESTPARSER_H


#include <optional>
#include <tuple>
#include <variant>
#include <charconv>
#include "ClientRequest.h"

class ClientRequestParser {

public:
    std::variant<ClientRequest, const char*> parse(std::string_view to_parse) {
        //must start with Login
        if(auto result = starts_with("LOGIN", to_parse);
           auto remainder = std::get_if<std::string_view>(&result)) {
            //followed by newline
            if (auto match_result = starts_with('\n', *remainder);
                    auto match_remainder = std::get_if<std::string_view>(&match_result)) {
                //until next newline is username
                if (auto capture_user_result = match_until("\n", *match_remainder);
                        auto capture_user = std::get_if<std::tuple<std::string_view, std::string_view >>(
                                &capture_user_result)) {
                    //until next newline is password
                    if (auto capture_pw_result = match_until("\n", std::get<1>(*capture_user));
                            auto capture_pw = std::get_if<std::tuple<std::string_view, std::string_view >>(
                                    &capture_pw_result)) {
                        //has to be finished
                        if (std::get<1>(*capture_pw).length() == 0) {
                            return Login{
                                    .username= std::string{std::get<0>(*capture_user)},
                                    .password= std::string{std::get<0>(*capture_pw)},
                            };
                        } else {
                            return "ERR";
                        }
                    } else { return std::get<1>(capture_pw_result); }

                } else { return std::get<1>(capture_user_result); }

            } else { return std::get<1>(match_result); }

        }else if(auto result = starts_with("SEND", to_parse);
                 auto remainder = std::get_if<std::string_view >(&result)){
            if(auto match_result = starts_with('\n', *remainder);
                auto match_remainder = std::get_if<std::string_view>(&match_result)) {
                //match receiver
                if(auto capture_recv_result = match_until("\n", *match_remainder);
                    auto capture_recv = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_recv_result)){
                    //match subject
                    if(auto capture_subject_result = match_until("\n", std::get<1>(*capture_recv));
                        auto capture_subject = std::get_if<std::tuple<std::string_view, std::string_view >>(&capture_subject_result)) {

                        if(auto capture_msg_result = match_until("\n.\n", std::get<1>(*capture_subject));
                            auto capture_msg  = std::get_if<std::tuple<std::string_view, std::string_view>>(&capture_msg_result)){
                            return Send {
                                .to = std::string{std::get<0>(*capture_recv)},
                                .subject = std::string{std::get<0>(*capture_subject)},
                                .msg = std::string{std::get<0>(*capture_msg)}
                            };
                        }else{ return std::get<1>(capture_msg_result);}
                    }else{ return std::get<1>(capture_subject_result);}
                }else{ return std::get<1>(capture_recv_result);}
            }else{ return std::get<1>(match_result); }

        //starts with LIST
        }else if(auto result = starts_with("LIST", to_parse);
                 auto remainder = std::get_if<std::string_view>(&result)){
            //followed by newline
            if(auto match_result = starts_with('\n', *remainder);
               auto match_remainder = std::get_if<std::string_view>(&match_result)) {
                //must end here
                if (match_remainder->length() == 0) {
                    return List{};
                } else { return "ERR"; }
            }else{ return std::get<1>(match_result); }



        //starts with READ
        }else if(auto result = starts_with("READ", to_parse);
                 auto remainder = std::get_if<std::string_view>(&result)){
            //followed by newline
            if(auto match_result = starts_with('\n', *remainder);
               auto match_remainder = std::get_if<std::string_view>(&match_result)) {
                //until newline is mail id
                if(auto capture_id_result = match_until("\n", *match_remainder);
                   auto capture_id = std::get_if<std::tuple<std::string_view , std::string_view>>(&capture_id_result)) {
                    //captured string must be a number and input is finished
                    if (msg_id id;std::from_chars(std::get<0>(*capture_id).begin(), std::get<0>(*capture_id).end(), id, 10).ec != std::errc::invalid_argument
                    && std::get<1>(*capture_id).length() == 0) {
                        return Read{
                                .id = id
                        };
                    } else {
                        return "ERR";
                    }
                }else{ return std::get<1>(capture_id_result); }
            }else{ return std::get<1>(match_result);}


        }else if(auto result = starts_with("DELETE", to_parse);
                 auto remainder = std::get_if<std::string_view>(&result)){

            //followed by newline
            if(auto match_result = starts_with('\n', *remainder);
                    auto match_remainder = std::get_if<std::string_view>(&match_result)) {
                //until newline is mail id
                if(auto capture_id_result = match_until("\n", *match_remainder);
                        auto capture_id = std::get_if<std::tuple<std::string_view , std::string_view>>(&capture_id_result)) {
                    //captured string must be a number and input is finished
                    if (msg_id id;std::from_chars(std::get<0>(*capture_id).begin(), std::get<0>(*capture_id).end(), id, 10).ec != std::errc::invalid_argument
                    && std::get<1>(*capture_id).length() == 0) {
                        return Delete{
                                .id = id
                        };
                    } else {
                        return "ERR";
                    }
                }else{ return std::get<1>(capture_id_result); }
            }else{ return std::get<1>(match_result);}

        }else if (auto result = starts_with("QUIT", to_parse);
                  auto remainder = std::get_if<std::string_view>(&result)) {

            if(auto match_result = starts_with('\n', *remainder);
                    auto match_remainder = std::get_if<std::string_view>(&match_result)) {
                //must end here
                if (match_remainder->length() == 0) {
                    return Quit{};
                } else { return "ERR"; }
            }else{ return std::get<1>(match_result); }

        }else{
            return "ERR";
        }
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


/*
  if (to_parse.find("LOGIN", 0) == 0) {
            to_parse = to_parse.substr(5, to_parse.length());
            if(to_parse.length() > 0){
                if(to_parse[0] == '\n'){
                   auto substr = to_parse.substr(1, to_parse.length()).find('\n');
                    if(substr >= 0){
                        if(substr > 8){
                            return "ERR";
                        }else{
                            std::string_view username = to_parse.substr(1, substr);
                            to_parse = to_parse.substr(substr, to_parse.length());
                            if(to_parse.length() > 0) {
                                if (to_parse[0] == '\n') {
                                    to_parse = to_parse.substr(1, to_parse.length());
                                    if(to_parse.length() > 0){
                                        auto substr =
                                    }else{
                                        return "incomplete";
                                    }

                                } else {
                                    return "ERR";
                                }
                            }else{
                                return "incomplete";
                            }
                        }
                    }else{
                        return "incomplete";
                    }
                } else {
                    return "ERR";
                }
            } else {
                return "incomplete";
            }
  */

#endif //VSYS_SOCKET_CLIENTREQUESTPARSER_H
