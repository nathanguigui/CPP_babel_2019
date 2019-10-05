
#include "mainWindow.hpp"

int main(int argc, char *argv[])
{

    qDebug() << "toto";
    
    // Creates an instance of QApplication
    QApplication app(argc, argv); 
    MainWindow mainWindow;
    // launch login page
    QString login = mainWindow.launchlogin();
    mainWindow.centerAndResize();
    if (login == "NULL")
        return 0;
    std::string str = login.toStdString();
    auto host = std::string(SERVER_IP);
    std::string device = "perceval";
    std::string callId = "guigui";
    auto *sessionManager = new SessionManager(host, 25565, str, device, callId, &mainWindow);
    sessionManager->Register();
    sessionManager->updateData();
    mainWindow.setManager(sessionManager);
    // splash screen
    mainWindow.launchSplashScreen();
    mainWindow.importContact();
    // run the application and return execs() return value/code
    return app.exec();

}