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
#include <vector>

class Database {
public:
    explicit Database(const char * filename);
    Database();
    virtual ~Database();
    void save_msg(Mail_in msg);
    void delete_msg(uint16_t msg_id);
    std::vector<Mail_out> getMsgFor(std::string uid);

private:
    sqlite3 *db;
    const char * filename;
    std::string get_home() const;
    void create_tables();
    void open_database();
    void executeStatement(std::string statement,
            int(*callback)(void*, int, char**, char**),
            void * result,
            std::string errMsg,
            std::string sucessMsg);
    inline bool db_exists() const;

    static int getMsgCallback(void *, int, char**, char**);
};

#define VSYS_SOCKET_DATABASE_H



#endif //VSYS_SOCKET_DATABASE_H