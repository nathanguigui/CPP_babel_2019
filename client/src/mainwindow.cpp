//
// Created by guigui on 9/17/19.
//

#include "mainWindow.hpp"

// Constructor for main widget
MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{

   // button
   button_ = new QPushButton("quit", this);

   // text browser
   textBrowser_ = new QTextBrowser();

   // text box
   textBox_  = new QTextEdit();

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,2,3);
   mainLayout->addWidget(textBrowser_,1,1);
   mainLayout->addWidget(textBox_,1,3);
   this->setStyleSheet("background-color: rgb(38,38,38);");
   button_->setStyleSheet("background-color: rgb(255, 255, 255);");
   textBox_->setStyleSheet("background-color: rgb(255, 255, 255);");
   textBrowser_->setStyleSheet("background-color: rgb(255, 255, 255);");
   setLayout(mainLayout);
   setWindowTitle(tr("BABEL"));
   connect(button_, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}

// Destructor
MainWindow::~MainWindow()
{
   delete textBox_;
   delete button_;
   delete textBrowser_;
}

QString MainWindow::launchlogin()
{
   QInputDialog *log = new QInputDialog(this);
   log->setLabelText(tr("Enter login: "));
   log->setWindowTitle(tr("Login"));
   log->adjustSize();
   log->setStyleSheet("background-color: rgb(255, 255, 255);");
   log->move(QApplication::desktop()->screen()->rect().center() - log->rect().center());
   if (log->exec() == QDialog::Accepted)
      login = log->textValue();
   else
      exit(0);
   qDebug() << login;
   return login;
}

void MainWindow::launchSplashScreen()
{
   QMovie *splash = new QMovie("../client/templates/cube.gif");
   QLabel *processLabel = new QLabel(this);
   //QMediaPlayer *sound = new QMediaPlayer;
   //sound->setMedia(QUrl::fromLocalFile("../client/templates/launch.mp3");
   //sound->setVolume(50);
   processLabel->resize(980, 580);
   processLabel->setStyleSheet("background-color: rgb(38,38,38);");
   processLabel->setMovie(splash);
   processLabel->setWindowFlags(Qt::FramelessWindowHint);
   processLabel->setAlignment(Qt::AlignCenter);
   splash->start();
   processLabel->show();
   //QTimer::singleShot(3500, sound, SLOT(close()));
   QTimer::singleShot(3500, processLabel, SLOT(close()));
   QTimer::singleShot(0, this, SLOT(show()));
}

void MainWindow::centerAndResize()
{
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "dimensions " << width << "x" << height;
   width *= 0.5;
   height *= 0.5;
   qDebug() << "Computed dimensions" << width << "x" << height;
   QSize newSize( width, height );

   setGeometry(
      QStyle::alignedRect(
         Qt::LeftToRight,
         Qt::AlignCenter,
         newSize,
         qApp->desktop()->availableGeometry()
      )
   );
}