//
// Created by viktorl on 02.10.18.
//

#include "include/Database.h"

Database::Database()
        : Database((get_home() + "/.mail.db").c_str())
{}

Database::Database(const char * filename) : filename(filename) {
    open_database();
    setup_tables();
}

Database::~Database() {
    sqlite3_close(db);
}

std::string Database::get_home() const {
    const char *homedir = nullptr;
    if ((homedir = getenv("HOME"))) {
        homedir = getpwuid(getuid())->pw_dir;
    } else {
        return "";
    }
    return std::string(homedir);
}

void Database::open_database() {
    if (sqlite3_open(filename, &db)) {
        std::stringstream ss("Failed creating/opening database: ");
        ss << sqlite3_errmsg(db);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << "Opened database successfully." << std::endl;
    }
}

bool Database::db_exists() const {
    struct stat buffer{};
    return (stat(filename, &buffer) == 0);
}

void Database::setup_tables() {
    std::string sql = "CREATE TABLE IF NOT EXISTS MAIL("
                      "mail_ID   INTEGER PRIMARY KEY,"
                      "subject   TEXT    NOT NULL,"
                      "payload   TEXT    NULL,"
                      "from_uid      TEXT    NOT NULL,"
                      "to_uid        TEXT    NOT NULL);";
    std::string errMsg = "Failed creating tables. ";
    std::string successMsg = "Tables were created successfully. ";
    executeStatement(sql, nullptr, nullptr, errMsg, successMsg);
}

void Database::save_msg(Mail_in mail_in) {
    std::stringstream sql;
    sql << "INSERT INTO MAIL(subject, payload, from_uid, to_uid)"
        << "VALUES("
        << "\'" << mail_in.subject
        << "\',\'" << mail_in.payload
        << "\',\'" << mail_in.from
        << "\',\'" << mail_in.to
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

std::optional<Mail_out> Database::getMsg(std::string mail_id) {
    std::string sql = "SELECT * FROM MAIL WHERE mail_id = \'" + mail_id + "\';";
    std::string successMsg = "Retrieving message was successful.";
    std::string errMsg = "Failed to retrieve message. ";
    std::vector<Mail_out> result{};
    executeStatement(sql, getMsgsCallback, &result, errMsg, successMsg);
    if(!result.empty()) {
        return result.at(0);
    } else {
        return std::nullopt;
    }
}

/**
 * returns all msgs for uid
 */
std::vector<Mail_out> Database::getMsgFor(std::string uid) {
    std::string sql = "SELECT * FROM MAIL WHERE MAIL.to_uid = \'" + uid + "\';";
    std::string successMsg = "Retrieving data was successful.";
    std::string errMsg = "Failed to retrieve data. ";
    std::vector<Mail_out> result{};
    executeStatement(sql, getMsgsCallback, &result, errMsg, successMsg);
    return result;
}

void Database::executeStatement(std::string statement,
                                int(*callback)(void *, int, char **, char **),
                                void * result,
                                std::string errorMsg,
                                std::string successMsg) {
    char *sqlError = nullptr;
    if ((sqlite3_exec(db, statement.c_str(), callback, result, &sqlError)) != SQLITE_OK) {
        std::stringstream ss{};
        ss << errorMsg;
        ss << sqlError;
//        free(sqlError);
        throw std::runtime_error(ss.str());
    } else {
        std::cout << successMsg << std::endl;
    }
}

int Database::getMsgsCallback(void *msg, int argc, char **argv, char **azColName) {
    if(argc == 5) {
        Mail_out m = {
                .id = argv[0],
                .subject = argv[1],
                .payload = argv[2],
                .from = argv[3],
                .to = argv[4]
        };
        auto *msgs = (std::vector<Mail_out> *)msg;
        msgs->push_back(m);
    } else {
        std::cout << "Initializing object failed." << std::endl;
        return 1;
    }
    return 0;
}






