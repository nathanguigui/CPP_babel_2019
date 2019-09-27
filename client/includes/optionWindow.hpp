//
// headers
//

#ifndef OPTIONWINDOW_H_
#define OPTIONWINDOW_H_

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

class QTextEdit;
class QPushButton;
class MainWindow;

class OptionWindow: public QWidget
{
    Q_OBJECT
    public:
        explicit OptionWindow(QWidget *parent = 0);
        ~OptionWindow();

        void setMainWindow(MainWindow *m) { mainwindow = m; };
        void centerAndResize();

    public slots:
        void colorSend();
        void colorCall();
        void colorAdd();

    private:
        MainWindow *mainwindow;
        QPushButton *button_save;
        QPushButton *button_cancel;
        QPushButton *button_col_send;
        QPushButton *button_col_call;
        QPushButton *button_col_add;
};

#endif