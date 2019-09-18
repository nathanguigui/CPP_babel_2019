
#include "mainWindow.hpp"
#include "loginWindow.hpp"

int main(int argc, char *argv[])
{

    qDebug() << "toto";
    
    // Creates an instance of QApplication
    QApplication app(argc, argv);

    //network

    // This is our MainWidget class containing our GUI and functionality
    loginWindow login;
    login.show();
    login.centerAndResize();
    //window.openLoginWindow(); // Show main window

    // run the application and return execs() return value/code
    return app.exec();
}