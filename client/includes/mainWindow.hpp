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
#include <iostream>
#include <iterator>
#include <map>
#include "optionWindow.hpp"
#include "UISettings.hpp"
#include "contactWindow.hpp"
#include "contact.hpp"


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

        //UPDATE
        void updateMainColor(QString color) { settings_->setMainColor(color); contact_name_->setStyleSheet(settings_->getLabel()); this->setStyleSheet(settings_->getMainWindow()); };
        void updateFont(QString font) { /* NEX UPDATE  */ };
        void updateSize(int size) { settings_->setSize(size); this->setStyleSheet(settings_->getMainWindow()); };
        void updateWindowSize(int width, int height);

        void updateButtonSend(QString color) { settings_->setButtonSend(color); button_send_->setStyleSheet(settings_->getButtonSend()); };
        void updateButtonAdd(QString color) { settings_->setButtonAdd(color); button_contact_->setStyleSheet(settings_->getButtonAdd()); };
        void updateButtonCall(QString color) { settings_->setButtonCall(color); button_call_->setStyleSheet(settings_->getButtonSend()); };

        void updateActiveImage(int value);
        void updateMessageBox(QString url) { settings_->setMessage(url); list_messages_->setStyleSheet(settings_->getMessage()); };
        void updateContactBox(QString url) { settings_->setContact(url); list_->setStyleSheet(settings_->getContact()); };
        void updateTextBox(QString url) { settings_->setText(url); textBox_->setStyleSheet(settings_->getText()); };

    public slots:
        void addContact();
        void showOptions();
        void call();
        void sendMessage();
        void setName(QListWidgetItem*);
        
    private:
        UISettings *settings_;
        QString login;
        QListWidgetItem *nom_contact;
        QListWidget *list_;
        QListWidget *list_messages_;
        QTextEdit* textBox_;
        QPushButton* button_contact_;
        QPushButton* button_call_;
        QPushButton* button_send_;
        QLabel *contact_name_;
        QToolBar *toolbar_;
        std::map<std::string, contact *> contact_list;
};
#endif // MAINWINDOW_H