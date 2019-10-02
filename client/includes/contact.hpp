//
// Created by glithaud on 10/2/19.
//

#ifndef CPP_BABEL_2019_CONTACT_HPP
#define CPP_BABEL_2019_CONTACT_HPP

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

class contact : public QWidget
{
public:
    explicit contact(QString login, QString ip, bool state, QWidget *parent = 0);
    ~contact();

    ///SendMessage
    ///CallContact
private:
    QString loginName_;
    QString ip_;
    bool state_;
    bool isPrint_;
};

#endif //CPP_BABEL_2019_CONTACT_HPP
