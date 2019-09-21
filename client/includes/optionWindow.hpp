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

class QTextEdit;
class QPushButton;

class OptionWindow: public QWidget
{
    Q_OBJECT
    public:
        explicit OptionWindow(QWidget *parent = 0);
        ~OptionWindow();

        void centerAndResize();

    private:
        QPushButton *button_save;
        QPushButton *button_cancel;      
};

#endif