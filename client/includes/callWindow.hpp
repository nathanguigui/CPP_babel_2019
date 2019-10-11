//
// headers
//

#ifndef CALLWINDOW_H_
#define CALLWINDOW_H_

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
#include "UISettings.hpp"
//#include "callThread.hpp"
#include "mainWindow.hpp"

class QPushButton;
class QTextBrowser;

class CallWindow: public QWidget
{
    Q_OBJECT
    public:
        explicit CallWindow(QWidget *parent = 0);
        //~CallWindow();

        void setMainWindow(MainWindow *m) { mainwindow = m; };
        void centerAndResize();
        int width;
        int height;
    
    signals:
        void endCall();

    public slots:
        void setWindow();
        void quitter();

    private:
        QTextBrowser *picture;
        MainWindow *mainwindow;
        QPushButton *button_quit;
};

#endif