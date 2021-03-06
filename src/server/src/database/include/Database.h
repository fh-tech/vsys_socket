//
// Created by viktorl on 02.10.18.
//
#ifndef VSYS_SOCKET_DATABASE_H
#define VSYS_SOCKET_DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <utility>
#include <sys/stat.h>
#include "Message.h"
#include <vector>
#include <Mail.h>
#include <optional>
#include <ctime>

class Database {
public:
    explicit Database(const char * filename);
    Database();
    virtual ~Database();
    void save_msg(Mail_in mail_in);
    void delete_msg(uint16_t mail_id);

    void ban_ip(uint32_t ip, std::time_t until);
    bool is_banned(uint32_t ip);


    std::vector<Mail_out> getMsgFor(std::string uid);
    std::optional<Mail_out> getMsg(std::string mail_id);

private:
    sqlite3 *db;
    const char * filename;
    std::string get_home() const;
    void setup_tables();
    void open_database();
    void executeStatement(std::string statement,
            int(*callback)(void*, int, char**, char**),
            void * result,
            std::string errorMsg,
            std::string successMsg);
    inline bool db_exists() const;

    static int getMsgsCallback(void *, int, char **, char **);
    static int is_banned_Callback(void *msg, int argc, char **argv, char **azColName);
};


#endif //VSYS_SOCKET_DATABASE_H
