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
#include "UISettings.hpp"

class QTextEdit;
class QPushButton;
class MainWindow;
class QGroupBox;
class QString;

class OptionWindow: public QWidget
{
    Q_OBJECT
    public:
        explicit OptionWindow(QWidget *parent = 0);
        ~OptionWindow();

        void setMainWindow(MainWindow *m) { mainwindow = m; };
        void centerAndResize();
        int width;
        int height;

    public slots:
        void colorSend();
        void colorCall();
        void colorAdd();
        void colorBack();
        void imageMessages();
        void imageContact();
        void imageText();
        void updateSize();
        void quitter();
        //void setFontSize();

    private:
        MainWindow *mainwindow;
        QPushButton *button_save;
        QPushButton *button_cancel;

        QPushButton *backgroundButton;
        
        QPushButton *message_button;
        QPushButton *contact_button;
        QPushButton *text_button;
       
        QGroupBox *WidgetImage();
        QGroupBox *colorGroupBox();
        QGroupBox *backgroundColorGroupBox();
        QGroupBox *fontGroupBox();
        QGroupBox *windowSizeGroupBox();

        QStringList fileMessages;
        QStringList fileContact;
        QStringList fileText;

        QSlider *slider;
        QSlider *slidervert;

        UISettings *settings_;

};
#endif