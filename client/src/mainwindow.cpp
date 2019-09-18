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

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,2,2);
   mainLayout->addWidget(textBrowser_,1,1);
   setLayout(mainLayout);
   setWindowTitle(tr("BABEL"));
   connect(button_, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}

// Destructor
MainWindow::~MainWindow()
{
   delete button_;
   delete textBrowser_;
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