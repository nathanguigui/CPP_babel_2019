
#include "mainWindow.hpp"

int main(int argc, char *argv[])
{

    qDebug() << "toto";
    
    // Creates an instance of QApplication
    QApplication app(argc, argv);

    //network
    std::cout << QNetworkInterface::interfaceFromName("wlp58s0").index();
    auto str = std::string("127.0.0.1");
    auto *socket = new UdpNetwork(str, 25565);
    socket->sendData("toto");
    socket->sendData("It works");
    socket->closeConnection();

    // This is our MainWidget class containing our GUI and functionality
    MainWindow window;
    window.centerAndResize();
    window.show(); // Show main window

    // run the application and return execs() return value/code
    return app.exec();
}
