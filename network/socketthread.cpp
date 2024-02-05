#include "socketthread.hpp"

#include "utility/dataformat/dataformat.hpp"

#include <string>
#include <iostream>

SocketThread::SocketThread(const QVariant& info)
    : QThread{nullptr}
{
    info_ = info;
}

void SocketThread::run()
{
    QTcpSocket socket;

    socket.connectToHost("114.116.115.205", 20000);
    if (!socket.waitForConnected()) {
        std::cerr << "warning: socket connect fail!\n";
        std::cerr << "error info: " << socket.errorString().toStdString() << '\n';
        return;
    }

    if (std::string tpnm = info_.typeName(); tpnm == "DataFormat::LoginClient") {
        login(socket);
    } else if (tpnm == "DataFormat::SignupClient") {
        signup(socket);
    } else {
        assert(false);
    }

    socket.close();
}

void SocketThread::login(QTcpSocket& socket)
{
    socket.write(DataFormat::serialize(info_.value<DataFormat::LoginClient>()));
    if (!socket.waitForReadyRead()) {
        std::cerr << "warning: socket read fail!\n";
        std::cerr << "error info: " << socket.errorString().toStdString() << '\n';
        return;
    }
    DataFormat::LoginServer logininfo = DataFormat::deSerialize<DataFormat::LoginServer>(socket.readAll());
    emit loginResult(logininfo.loginstate);
}

void SocketThread::signup(QTcpSocket &socket)
{
    socket.write(DataFormat::serialize(info_.value<DataFormat::SignupClient>()));
    if (!socket.waitForReadyRead()) {
        std::cerr << "warning: socket read fail!\n";
        std::cerr << "error info: " << socket.errorString().toStdString() << '\n';
        return;
    }
    DataFormat::SignupServer signupinfo = DataFormat::deSerialize<DataFormat::SignupServer>(socket.readAll());
    emit signupResult(signupinfo.signupstate);
}
