#include "database.hpp"

DataBase::DataBase()
{
    if (!init()) {
        qDebug() << "DataBase init fail!";
    }
}

DataBase::~DataBase()
{
    db.close();
}

DataBase &DataBase::getInstance()
{
    static DataBase instance;
    return instance;
}

bool DataBase::init()
{
    qDebug() << "DataBase::init...";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("account.db");
    if (!db.open()) {
        qDebug() << "Error: could not connect to database";
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS accounts (username TEXT PRIMARY KEY, password TEXT)");

    return true;
}

bool DataBase::login(const QString &username, const QString &password)
{
    bool flag = false;

    QSqlQuery query;
    QString querytext = QString("SELECT * FROM accounts WHERE username = '%0'").arg(username);
    if (query.exec(querytext)) {
        while (query.next()) {
            QString username1 = query.value(0).toString();
            QString password1 = query.value(1).toString();
            if (username1 == username && password1 == password) {
                flag = true;
                break;
            }
        }
    } else {
        qDebug() << "Error: could not retrieve data";
        flag = false;
    }

    return flag;
}

bool DataBase::signup(const QString &username, const QString &password)
{
    std::lock_guard<std::mutex> guard(mtx_);

    bool flag = true;

    QSqlQuery query;
    QString querytext = QString("SELECT * FROM accounts WHERE username = '%0'").arg(username);
    if (query.exec(querytext)) {
        while (query.next()) {
            flag = false;
            break;
        }
        if (flag) {
            QString writetext = QString(R"(INSERT INTO accounts (username, password) VALUES ("%0", "%1"))").arg(username, password);
            query.exec(writetext);
        }
    } else {
        qDebug() << "Error: could not retrieve data";
        flag = false;
    }

    return flag;
}
