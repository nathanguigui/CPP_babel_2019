#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtCore/QDebug>
#include <QtWidgets/QtWidgets>
#include <iostream>
#include <QtNetwork/QtNetwork>
#include <QUdpSocket>
#include <QSize>
#include <QTextEdit>
#include <QSplashScreen>
#include <QTimer>
#include <QMovie>

class QTextEdit;
class QPushButton;
class QTextBrowser;
class QListView;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwindow.cpp
class MainWindow : public QWidget
{
    public:
        explicit MainWindow(QWidget *parent = 0); //Constructor
        ~MainWindow(); // Destructor
        
        void centerAndResize();
        QString launchlogin();
        void launchSplashScreen();

    private:
        QString login;
        QListView *list_;
        QTextEdit* textBox_;
        QPushButton* button_contact_;
        QPushButton* button_send_;
        QPushButton* button_call_;
        QTextBrowser* textBrowser_;
};

#endif // MAINWINDOW_H