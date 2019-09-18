//
// Created by poirelZ
//

#include "loginWindow.hpp"

// Constructor for main widget
loginWindow::loginWindow(QWidget *parent): QWidget(parent)
{

   // button
   button_ = new QPushButton("login", this);

   // text browser
   textBox_  = new QTextEdit();

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,1,2);
   mainLayout->addWidget(textBox_,1,1);
   setLayout(mainLayout);
   setWindowTitle(tr("LOGIN PAGE"));
   connect(button_, SIGNAL(released()), this, SLOT(openMainWindow()));
}

// Destructor
loginWindow::~loginWindow()
{
   delete textBox_;
   delete button_;
}

void loginWindow::centerAndResize()
{
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "dimensions " << width << "x" << height;
   width *= 0.2;
   height *= 0.1;
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

void loginWindow::openMainWindow()
{
   mainWindow_ = new MainWindow();
   mainWindow_->show();
}