#ifndef DATAFORMAT_HPP
#define DATAFORMAT_HPP

#include <QString>
#include <QDataStream>
#include <QIODevice>

namespace DataFormat {

struct LoginClient {
    static constexpr qint8 type = 1;

    QString username;
    QString password;

    friend QDataStream& operator>>(QDataStream& in, LoginClient& rhs) {
        qint8 a;
        in >> a;
        in >> rhs.username >> rhs.password;
        return in;
    }
    friend QDataStream& operator<<(QDataStream& out, const LoginClient& rhs) {
        out << rhs.type << rhs.username << rhs.password;
        return out;
    }
};

struct LoginServer {
    static constexpr qint8 type = -1;

    bool loginstate;

    friend QDataStream& operator>>(QDataStream& in, LoginServer& rhs) {
        qint8 a;
        in >> a;
        in >> rhs.loginstate;
        return in;
    }
    friend QDataStream& operator<<(QDataStream& out, const LoginServer& rhs) {
        out << rhs.type << rhs.loginstate;
        return out;
    }
};

struct SignupClient {
    static constexpr qint8 type = 2;

    QString username;
    QString password;

    friend QDataStream& operator>>(QDataStream& in, SignupClient& rhs) {
        qint8 a;
        in >> a;
        in >> rhs.username >> rhs.password;
        return in;
    }
    friend QDataStream& operator<<(QDataStream& out, const SignupClient& rhs) {
        out << rhs.type << rhs.username << rhs.password;
        return out;
    }
};

struct SignupServer {
    static constexpr qint8 type = -2;

    bool signupstate;

    friend QDataStream& operator>>(QDataStream& in, SignupServer& rhs) {
        qint8 a;
        in >> a;
        in >> rhs.signupstate;
        return in;
    }
    friend QDataStream& operator<<(QDataStream& out, const SignupServer& rhs) {
        out << rhs.type << rhs.signupstate;
        return out;
    }
};

template<class T>
QByteArray serialize(const T& info) {
    QByteArray bytes;
    QDataStream datastream(&bytes, QIODevice::WriteOnly);
    datastream << info;
    return bytes;
}

template<class T>
T deSerialize(QByteArray& bytes) {
    T info;
    QDataStream datastream(&bytes, QIODevice::ReadOnly);
    datastream >> info;
    return info;
}

template<class T>
T deSerialize(QByteArray&& bytes) {
    T info;
    QDataStream datastream(&bytes, QIODevice::ReadOnly);
    datastream >> info;
    return info;
}

}
Q_DECLARE_METATYPE(DataFormat::LoginClient)
Q_DECLARE_METATYPE(DataFormat::SignupClient)

#endif // DATAFORMAT_HPP
