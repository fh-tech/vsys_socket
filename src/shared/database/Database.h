//
// Created by viktorl on 02.10.18.
//




#ifndef VSYS_SOCKET_DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <sstream>

class Database {
public:
    explicit Database(std::string filename);
    ~Database();

private:
    sqlite3 *db;
};

#define VSYS_SOCKET_DATABASE_H



#endif //VSYS_SOCKET_DATABASE_H
