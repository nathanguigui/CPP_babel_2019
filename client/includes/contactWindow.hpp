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
//#include <contact.hpp>
//#include "mainWindow.hpp"
#include "UISettings.hpp"
#include "Network/AsyncSession.hpp"

class contact;
class QTextEdit;
class QPushButton;
class MainWindow;
class QGroupBox;
class QString;
class QListWidget;
class QStringList;

Q_DECLARE_METATYPE(std::vector<ContactDetails>);
Q_DECLARE_METATYPE(std::string);
//Q_DECLARE_METATYPE(std::vector<ContactDetails>);


class ContactWindow: public QWidget
{
    Q_OBJECT
    public:
        explicit ContactWindow(QWidget *parent = 0);
        ~ContactWindow();

        void setContactList(std::map<QString, contact *> list);
        void setMainWindow(MainWindow *m) { mainwindow = m; };
        void centerAndResize();
        void fillContact();

    public slots:

        void fillList(std::vector<ContactDetails>);
        void contactClicked(QListWidgetItem *);
        void addContact();
        void quitter();

    private:
        MainWindow *mainwindow;

        std::map<QString, contact *> contacts;
        QPushButton *buttonAdd;
        QPushButton *buttonQuit;

        QListWidget *contactList;

        UISettings *settings_;

        QString contactChosen;
        bool state;

        AsyncSession asyncSession;

};
#endif