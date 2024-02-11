/*

  What
  High performance multi-threaded TCP server

  Why
  Lets see how to make it fast

  How
  Code example
  Test with Siege
  https://www.joedog.org/siege-home/

  siege -c 1 127.0.0.1:20000
  siege -c 10 127.0.0.1:20000
  siege -c 100 127.0.0.1:20000

*/

#include <QCoreApplication>

#include "server.hpp"

#include <QString>

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (argc != 3) {
        std::cerr << "argc != 3\n";
        std::cerr << "miss ip and port\n";
        std::cerr << "e.g.: ./server 0.0.0.0 8080\n";
        std::exit(1);
    }

    QString ip = argv[1];
    quint16 port = QString(argv[2]).toUInt();

    qDebug() << "ip ==" << ip;
    qDebug() << "port ==" << port;

    Server server;
    server.start(ip, port);

    return app.exec();
}
