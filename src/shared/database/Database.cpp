//
// Created by viktorl on 02.10.18.
//

#include "Database.h"


Database::Database(std::string filename) : filename(std::move(filename)) {
    if (!db_exists()) create_tables();
}

Database::Database() : Database(get_home() + "/.mail.db") {}

Database::~Database() {
    sqlite3_close(db);
}

std::string Database::get_home() const {
    const char *homedir;
    if ((homedir = getenv("HOME")) == nullptr) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return std::string(homedir);
}

void Database::open_database() {
    if (sqlite3_open(filename.c_str(), &db)) {
        std::stringstream ss("Failed creating/opening database: ");
        ss << sqlite3_errmsg(db);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << "Opened database successfully." << std::endl;
    }
}

bool Database::db_exists() const {
    struct stat buffer{};
    return (stat(filename.c_str(), &buffer) == 0);
}

void Database::create_tables() {
    std::string sql = "CREATE TABLE MAIL("
                      "mail_ID   INTEGER PRIMARY KEY,"
                      "subject   TEXT    NOT NULL,"
                      "payload   TEXT    NULL,"
                      "from_uid      TEXT    NOT NULL,"
                      "to_uid        TEXT    NOT NULL);";
    std::string errMsg = "Failed creating tables. ";
    std::string successMsg = "Tables were created successfully. ";
    executeStatement(sql, nullptr, nullptr, errMsg, successMsg);
}

void Database::save_msg(Message msg) {
    std::stringstream sql;
    sql << "INSERT INTO MAIL(subject, payload, from_uid, to_uid)"
        << "VALUES("
        << "\'" << msg.subject
        << "\',\'" << msg.payload
        << "\',\'" << msg.from
        << "\',\'" << msg.to
        << "\');";
    std::string errMsg = "Failed to insert data. ";
    std::string successMsg = "Data inserted successfully.";
    executeStatement(sql.str(), nullptr, nullptr, errMsg, successMsg);
}

void Database::delete_msg(uint16_t mail_id) {
    std::string sql = "DELETE FROM MAIL WHERE MAIL.mail_id = \'" + std::to_string(mail_id) +"\';";
    std::string successMsg = "Deleting was successful. ";
    std::string errMsg = "Delete failed. ";
    executeStatement(sql, nullptr, nullptr, errMsg, successMsg);
}

/**
 * returns all msgs for uid
 */
std::vector<Message> Database::getMsgFor(std::string uid) {
    std::string sql = "SELECT * FROM MAIL WHERE MAIL.to_uid = \'" + uid + "\';";
    std::string successMsg = "Retrieving data was successful.";
    std::string errMsg = "Failed to retrieve data. ";
    std::vector<Message> result{};
    executeStatement(sql, getMsgCallback, &result, errMsg, successMsg);
    return result;
}

void Database::executeStatement(std::string statement,
                                int(*callback)(void *, int, char **, char **),
                                void * result,
                                std::string errorMsg,
                                std::string successMsg) {
    open_database();
    char *sqlError = nullptr;
    if ((sqlite3_exec(db, statement.c_str(), callback, result, &sqlError)) != SQLITE_OK) {
        std::stringstream ss(errorMsg);
        ss << sqlError;
        sqlite3_free(sqlError);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << successMsg << std::endl;
    }
    sqlite3_close(db);
}

int Database::getMsgCallback(void * msg, int argc, char **argv, char **azColName) {
    if(argc == 5) {
        Message m = Message(argv[1], argv[2], argv[3], argv[4]);
        auto *msgs = (std::vector<Message> *)msg;
        msgs->push_back(m);
    } else {
        std::cout << "Initializing object failed." << std::endl;
        return 1;
    }
    return 0;
}




