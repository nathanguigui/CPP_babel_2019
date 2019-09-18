#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtCore/QDebug>
#include <QtWidgets/QtWidgets>
#include <iostream>
#include "main.hpp"
#include <QtNetwork/QtNetwork>
#include <QUdpSocket>
#include <UdpNetwork.hpp>

int main(int argc, char *argv[])
{

    qDebug() << "toto";
        // Creates an instance of QApplication
    QApplication a(argc, argv);

    std::cout << QNetworkInterface::interfaceFromName("wlp58s0").index();
    auto str = std::string("127.0.0.1");
    auto *socket = new UdpNetwork(str, 25565);
    socket->sendData("toto");
    socket->sendData("It works");
    socket->closeConnection();

    // This is our MainWidget class containing our GUI and functionality
    MainWidget w;
    w.show(); // Show main window

    // run the application and return execs() return value/code
    return a.exec();
}
