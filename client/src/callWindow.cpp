//
//
//

#include "callWindow.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

CallWindow::CallWindow(QWidget *parent): QWidget(parent)
{
    button_quit = new QPushButton("End call", this);
    picture = new QTextBrowser();

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(button_quit, 1, 0);
    mainLayout->addWidget(picture, 0, 0);

    picture->setStyleSheet("border-image: url(/home/luc4s.p/3_modules/CPP/CPP_babel_2019/client/templates/micro.jpg) 0 0 0 0 stretch stretch");

    setLayout(mainLayout);
    setWindowTitle(tr("Call"));

    QObject::connect(button_quit, SIGNAL (released()), this, SLOT (quitter()));
}

void CallWindow::setWindow()
{
    this->show();
}

CallWindow::~CallWindow()
{
    //emit endCall();
    delete button_quit;
}   

void CallWindow::quitter()
{
    emit endCall();
    this->hide();

}

void CallWindow::centerAndResize()
{
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "dimensions " << width << "x" << height;
   width *= 0.08;
   height *= 0.12;
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

#pragma GCC diagnostic pop