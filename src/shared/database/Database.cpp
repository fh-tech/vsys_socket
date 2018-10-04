//
// Created by viktorl on 02.10.18.
//


#include "Database.h"


Database::Database(std::string filename) {
    if(sqlite3_open(filename.c_str(), &db)) {
        std::stringstream ss("Failed creating/opening database: ");
        ss << sqlite3_errmsg(db);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}
