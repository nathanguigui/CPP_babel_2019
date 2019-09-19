
#include "mainWindow.hpp"
#include "loginWindow.hpp"

int main(int argc, char *argv[])
{

    qDebug() << "toto";
    
    // Creates an instance of QApplication
    QApplication app(argc, argv);  
    MainWindow mainWindow;
    mainWindow.launchlogin();
    mainWindow.centerAndResize();

    // splash screen
    QMovie *splash = new QMovie("cube.gif");
    QLabel *processLabel = new QLabel(&mainWindow);

    processLabel->resize(980, 580);
    processLabel->setStyleSheet("background-color: rgb(38,38,38);");
    processLabel->setMovie(splash);
    processLabel->setWindowFlags(Qt::FramelessWindowHint);
    processLabel->setAlignment(Qt::AlignCenter);
    //processLabel->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,processLabel->size(),app.desktop()->availableGeometry()));

    splash->start();
    processLabel->show();
    QTimer::singleShot(5000, processLabel, SLOT(close()));
    QTimer::singleShot(0, &mainWindow, SLOT(show()));

    // run the application and return execs() return value/code
    return app.exec();

}