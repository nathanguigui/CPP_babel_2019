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

class QTextEdit;
class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwindow.cpp
class MainWindow : public QWidget
{
    public:
        explicit MainWindow(QWidget *parent = 0); //Constructor
        ~MainWindow(); // Destructor
        
        void centerAndResize();

    private:
        QTextEdit* textBox_;
        QPushButton* button_;
        QTextBrowser* textBrowser_;
};

#endif // MAINWINDOW_H