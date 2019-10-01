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
        ///Getter of settings about main window
        QString getMainWindow() const;
        int getFontSize() const;
        int getWidth() const;
        int getHeight() const;
        QString getLabel() const;

        ///Gettter about the button
        QString getButtonCall() const;
        QString getButtonSend() const;
        QString getButtonAdd() const;

        ///Getter about the image background
        int getActiveImage() const;
        QString getMessage() const;
        QString getContact() const;
        QString getText() const;

        //SETTER
        ///Setter of main window
        void setMainColor(QString);
        void setFont(QString);
        void setSize(int);
        void setWidth(int width);
        void setHeight(int height);

        ///Setter about color's buttons
        void setButtonSend(QString);
        void setButtonCall(QString);
        void setButtonAdd(QString);

        ///Setter about the backroung image
        void setActiveImage(int);
        void setMessage(QString);
        void setContact(QString);
        void setText(QString);

    private:
        QString *path;
};


#endif //CPP_BABEL_2019_UISETTINGS_HPP
