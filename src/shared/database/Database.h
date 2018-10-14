//
// Created by viktorl on 02.10.18.
//




#ifndef VSYS_SOCKET_DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <utility>
#include <sys/stat.h>
#include "Message.h"

class Database {
public:
    explicit Database(std::string filename);
    Database();
    virtual ~Database();
    void save_msg(Message msg);
    void delete_msg(uint16_t msg_id);
    void getMsgFor(std::string uid);

private:
    sqlite3 *db;
    std::string filename;
    std::string get_home() const;
    void create_tables();
    void open_database();
    void executeStatement(std::string statement, std::string errMsg, std::string sucessMsg);
    inline bool db_exists() const;
};

#define VSYS_SOCKET_DATABASE_H



#endif //VSYS_SOCKET_DATABASE_H
