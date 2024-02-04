#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QtSql>
#include <QString>

#include <mutex>

class DataBase {
private:
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;

    DataBase();
    ~DataBase();

    QSqlDatabase db;
    std::mutex mtx_;

public:
    static DataBase& getInstance();

    bool init();
    bool login(const QString& username, const QString& password);
    bool signup(const QString& username, const QString& password);
};

#endif // DATABASE_HPP
