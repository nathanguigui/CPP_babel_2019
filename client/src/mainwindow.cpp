//
// Created by guigui on 9/17/19.
//

#include "../includes/mainWindow.hpp"

// Constructor for main widget
MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{

   // button
   button_contact_ = new QPushButton("Add contact", this);
   button_send_ = new QPushButton("Send", this);
   button_call_ = new QPushButton("Call", this);

   // text box
   textBox_  = new QTextEdit();

   // list view
   list_ = new QListWidget();
   list_messages_ = new QListWidget();
   list_->setSelectionMode(QAbstractItemView::SingleSelection);

   // com contact
   contact_name_ = new QLabel();

   QAction *quitter = new QAction("&Quit", this);
   QAction *deconnexion = new QAction("&Disconnect", this);
   QAction *options = new QAction("&Options", this);


   // ToolBar object
   toolbar_ = new QToolBar();
   toolbar_->addAction(options);
   toolbar_->addAction(deconnexion);
   toolbar_->addAction(quitter);
   toolbar_->setOrientation(Qt::Horizontal);
   QBoxLayout *toolLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
   toolLayout->setContentsMargins(0, 0, 0, 0);
   toolLayout->addWidget(toolbar_);
   connect(quitter, &QAction::triggered, this, &QApplication::quit);
   connect(deconnexion, &QAction::triggered, this, &MainWindow::launchlogin);
   connect(options, &QAction::triggered, this, &MainWindow::showOptions);

   QGridLayout *mainLayout = new QGridLayout;
   toolLayout->addLayout(mainLayout);
   mainLayout->setHorizontalSpacing(20);
   mainLayout->setVerticalSpacing(20);
   mainLayout->setContentsMargins(20, 20, 20, 20);
   mainLayout->addWidget(contact_name_,1, 1);
   mainLayout->addWidget(button_contact_,14, 7, 1, 3);
   mainLayout->addWidget(button_send_, 13, 6);
   mainLayout->addWidget(button_call_, 14, 6);
   mainLayout->addWidget(list_messages_, 1, 1, 12, 6);
   mainLayout->addWidget(textBox_, 13, 1, 2, 5);
   mainLayout->addWidget(list_, 0, 7, 14, 3);
   toolbar_->setStyleSheet("background-color: rgb(255,255,255);");

   this->setStyleSheet("background-color: #F7F7F7;");
   button_send_->setStyleSheet("background-color: rgb(30, 142, 152);border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;");
   button_contact_->setStyleSheet("background-color: rgb(231, 156, 15); border: 1px solid black; border-radius: 10px; height: 30px; color: white; font-weight: bold;");
   button_call_->setStyleSheet("background-color: crimson ; border: 1px solid black; border-radius: 10px;  height: 40px; color: white; font-weight: bold;");
   textBox_->setStyleSheet("background-color: rgb(255, 255, 255);border: 1px solid black; border-radius: 7px;");
   list_messages_->setStyleSheet("background-color: rgb(255, 255, 255); border: 1px solid black; border-radius: 7px;");
   list_->setStyleSheet("background-color: rgb(255, 255, 255); border: 1px solid black; border-radius: 7px;");
   contact_name_->setStyleSheet("background-color: #F7F7F7 ;border: 1px solid black; border-radius: 7px;");
   setLayout(mainLayout);
   setWindowTitle(tr("BABEL"));
   QObject::connect(button_contact_, SIGNAL (released()), this, SLOT (addContact()));
   QObject::connect(button_send_, SIGNAL(released()), this, SLOT(sendMessage()));
   QObject::connect(button_call_, SIGNAL(released()), this, SLOT(call()));
   //QObject::connect(list_, SIGNAL (itemSelectionChanged()), this, SLOT (setName()));
}

// Destructor
MainWindow::~MainWindow()
{
   delete textBox_;
   delete button_contact_;
   delete button_send_;
   delete button_call_;
   delete list_messages_;
   delete list_;
}

//void MainWindow::setName()
//{
//   qDebug() << "toto";
//   QString usr_name = list_->selectedItems();
//   qDebug() << usr_name;
//   contact_name_->setText(usr_name);
//}

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

QString MainWindow::addContact()
{
   QInputDialog *contact = new QInputDialog(this);
   contact->setLabelText(tr("Contact name or login:"));
   contact->setWindowTitle(tr("Add contact"));
   contact->adjustSize();
   contact->setStyleSheet("background-color: rgb(255, 255, 255);");
   contact->move(QApplication::desktop()->screen()->rect().center() - contact->rect().center());
   if (contact->exec() == QDialog::Accepted)
   {
      nom_contact = contact->textValue();
      this->list_->addItem(nom_contact);
   }
   else
      return nom_contact;
   qDebug() << nom_contact;
   return nom_contact;
}

void MainWindow::sendMessage()
{
    QString message;
    message = this->textBox_->toPlainText();
    qDebug() << message;
    this->textBox_->clear();
}

void MainWindow::call()
{
    qDebug() << "make a call";
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

void MainWindow::showOptions()
{
   OptionWindow *options = new OptionWindow();
   options->centerAndResize();
   options->show();
}