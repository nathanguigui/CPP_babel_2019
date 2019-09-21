#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtCore/QDebug>
#include <QtWidgets/QtWidgets>
#include <iostream>
#include <QSize>
#include <QTextEdit>
#include <QSplashScreen>
#include <QTimer>
#include <QMovie>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QApplication>
#include "optionWindow.hpp"


class QTextEdit;
class QPushButton;
class QTextBrowser;
class QListWidget;
class QLabel;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwindow.cpp
class MainWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0); //Constructor
        ~MainWindow(); // Destructor
        
        void centerAndResize();
        QString launchlogin();
        void launchSplashScreen();
        
    public slots:
        QString addContact();
        void showOptions();
        //void setName();

    private:
        QString login;
        QString nom_contact;
        QListWidget *list_;
        QListWidget *list_messages_;
        QTextEdit* textBox_;
        QPushButton* button_contact_;
        QPushButton* button_send_;
        QPushButton* button_call_;
        QLabel *contact_name_;
        QToolBar *toolbar_;
};
#endif // MAINWINDOW_H