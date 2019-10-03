
#include "mainWindow.hpp"


int main(int argc, char *argv[])
{

    qDebug() << "toto";
    
    // Creates an instance of QApplication
    QApplication app(argc, argv); 
    MainWindow mainWindow;
    // launch login page
    mainWindow.launchlogin();
    mainWindow.centerAndResize();

    // splash screen
    mainWindow.launchSplashScreen();

    // run the application and return execs() return value/code
    return app.exec();

}