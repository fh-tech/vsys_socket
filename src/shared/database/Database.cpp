//
// Created by viktorl on 02.10.18.
//


#include "Database.h"



Database::Database(std::string filename):filename(std::move(filename)) {
    if(!db_exists()) create_tables();
}

Database::Database():Database(get_home() + "/.mail.db") {}

Database::~Database() {
    sqlite3_close(db);
}

std::string Database::get_home() const {
    const char * homedir;
    if((homedir = getenv("HOME")) == nullptr) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return std::string(homedir);
}

void Database::open_database() {
    if(sqlite3_open(filename.c_str(), &db)) {
        std::stringstream ss("Failed creating/opening database: ");
        ss << sqlite3_errmsg(db);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << "Opened database successfully." << std::endl;
    }
}

bool Database::db_exists() const {
    struct stat buffer{};
    return (stat (filename.c_str(), &buffer) == 0);
}

void Database::create_tables() {
    std::string sql = "CREATE TABLE MAIL("
                         "mail_ID   SERIAL  PRIMARY KEY,"
                         "subject   TEXT    NOT NULL,"
                         "payload   TEXT    NULL,"
                         "from_uid      TEXT    NOT NULL,"
                         "to_uid        TEXT    NOT NULL);";
    std::string errMsg = "Failed creating tables. ";
    std::string successMsg = "Tables were created successfully. ";
    executeStatement(sql, errMsg, successMsg);
}

void Database::save_msg(Message msg) {
    open_database();
    std::string sql = "INSERT INTO MAIL(subject, payload, from_uid, to_uid)"
                      "VALUES(" + msg.subject + "," + msg.payload + "," + msg.from + "," + msg.to + ");";
    std::string errMsg = "Failed to insert data. ";
    std::string successMsg = "Data inserted successfully";
    executeStatement(sql, errMsg, successMsg);
}

void Database::delete_msg(uint16_t msg_id) {
    return;
}

/**
 * returns all msgs for uid
 */
void Database::getMsgFor(std::string uid) {
    return;
}

void Database::executeStatement(std::string statement, std::string errorMsg, std::string successMsg) {
    open_database();
    char * sqlError = 0;
    if((sqlite3_exec(db, statement.c_str(), NULL, NULL, &sqlError)) != SQLITE_OK) {
        std::stringstream ss(errorMsg);
        ss << sqlError;
        sqlite3_free(sqlError);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << successMsg << std::endl;
    }
    sqlite3_close(db);
}




