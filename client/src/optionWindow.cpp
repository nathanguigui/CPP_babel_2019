//
//
//

#include "../includes/optionWindow.hpp"

OptionWindow::OptionWindow(QWidget *parent): QWidget(parent)
{
    button_save = new QPushButton("Save", this);
    button_cancel = new QPushButton("Cancel", this);
    button_col_send = new QPushButton("Color Send Button", this);
    button_col_call = new QPushButton("Color Call Button", this);
    button_col_add = new QPushButton("Color Add Button", this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_col_send, 0,1);
    mainLayout->addWidget(button_col_call, 0, 2);
    mainLayout->addWidget(button_col_add, 0, 3);
    mainLayout->addWidget(button_save,1,2);
    mainLayout->addWidget(button_cancel, 1, 1);
    setLayout(mainLayout);
    setWindowTitle(tr("Options"));

    QObject::connect(button_col_send, SIGNAL (released()), this, SLOT (colorSend()));
    QObject::connect(button_col_call, SIGNAL (released()), this, SLOT (colorCall()));
    QObject::connect(button_col_add, SIGNAL (released()), this, SLOT (colorAdd()));
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

void OptionWindow::colorSend()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        qDebug() << "Color Choosen : " << color.name();
        QString qss = QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color.name());
        mainwindow->button_send_->setStyleSheet(qss);
    }
}

void OptionWindow::colorCall()
{}

void OptionWindow::colorAdd()
{}