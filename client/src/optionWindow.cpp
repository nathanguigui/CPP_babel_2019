//
//
//

#include "../includes/optionWindow.hpp"

OptionWindow::OptionWindow(QWidget *parent): QWidget(parent)
{
    button_save = new QPushButton("Save", this);
    button_cancel = new QPushButton("Cancel", this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_save,0,2);
    mainLayout->addWidget(button_cancel, 0, 1);
    setLayout(mainLayout);
    setWindowTitle(tr("Options"));

}

OptionWindow::~OptionWindow()
{
   delete button_save;
   delete button_cancel;
}

void OptionWindow::centerAndResize()
{
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "dimensions " << width << "x" << height;
   width *= 0.2;
   height *= 0.6;
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