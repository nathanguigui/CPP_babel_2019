//
// headers
//

#ifndef CONTACTWINDOW_H_
#define CONTACTWINDOW_H_

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
#include <QColorDialog>
#include "mainWindow.hpp"
#include "UISettings.hpp"

class QTextEdit;
class QPushButton;
class MainWindow;
class QGroupBox;
class QString;
class QListWidget;

class ContactWindow: public QWidget
{
    Q_OBJECT
    public:
        explicit ContactWindow(QWidget *parent = 0);
        ~ContactWindow();

        void setMainWindow(MainWindow *m) { mainwindow = m; };
        void centerAndResize();

    public slots:

        void addContact();

    private:
        MainWindow *mainwindow;

        QPushButton *buttonAdd;

        QListWidget *contactList;

        UISettings *settings_;
};
#endif