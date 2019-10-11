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

    setLayout(mainLayout);
    setWindowTitle(tr("In Call"));

    QObject::connect(button_quit, SIGNAL (released()), this, SLOT (quitter()));

}

CallWindow::~CallWindow()
{
    delete button_quit;
}

void CallWindow::quitter()
{
   this->~CallWindow();
}

void CallWindow::centerAndResize()
{
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "dimensions " << width << "x" << height;
   width *= 0.15;
   height *= 0.15;
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