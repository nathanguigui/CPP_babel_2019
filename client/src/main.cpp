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
#include <Network/SipManager.hpp>

int main(int argc, char *argv[])
{

    qDebug() << "toto";
        // Creates an instance of QApplication
    QApplication a(argc, argv);

    std::cout << QNetworkInterface::interfaceFromName("wlp58s0").index();
    auto host = std::string("127.0.0.1");
    auto username = std::string("guigui");
    auto localDeviceID = std::string("793d671c");
    auto callID = std::string("M2M2NDYxZjY1OGFjOWE5MTJmNWM2NjM2M2UwNDcxNjI.");
    auto SIP = new SipManager(host, 25565, username, localDeviceID, callID);

    SIP->Register();

    // This is our MainWidget class containing our GUI and functionality
    MainWidget w;
    w.show(); // Show main window

    // run the application and return execs() return value/code
    return a.exec();
}
