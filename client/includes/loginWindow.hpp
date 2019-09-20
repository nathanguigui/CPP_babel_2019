#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtCore/QDebug>
#include <QtWidgets/QtWidgets>
#include <iostream>
#include <QSize>
#include <QTextEdit>
#include "mainWindow.hpp"

class QTextEdit;
class QPushButton;

class loginWindow : public QWidget
{
    public:
        explicit loginWindow(QWidget *parent = 0);
        ~loginWindow();

        void centerAndResize();

    private slots:
        void openMainWindow();

    private:
        MainWindow *mainWindow_;
        QTextEdit *textBox_;
        QPushButton *button_;

};

#endif