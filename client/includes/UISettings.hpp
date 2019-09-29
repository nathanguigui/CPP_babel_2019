//
// Created by glithaud on 9/27/19.
//

#ifndef UISETTINGS_HPP
#define UISETTINGS_HPP


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

class QTextEdit;
class QPushButton;
class QTextBrowser;
class QListWidget;
class QLabel;

class UISettings :public QMainWindow {
    public:
        explicit UISettings(QWidget *parent = 0);
        virtual ~UISettings();

        void createSettings();

        // GETTER
        QString getMainWindow() const;

        QString getButtonCall() const;
        QString getButtonSend() const;
        QString getButtonAdd() const;

        QString getMessage() const;
        QString getContact() const;
        QString getText() const;

        //SETTER

        void setMainColor(QString);
        void setFont(QString);
        void setSize(int);
        void setHeight(int);
        void setWidth(int);

        void setButtonSend(QString);
        void setButtonCall(QString);
        void setButtonAdd(QString);

        void setMessage(QString);
        void setContact(QString);
        void setText(QString);

    private:
        QString *path;
};


#endif //CPP_BABEL_2019_UISETTINGS_HPP
