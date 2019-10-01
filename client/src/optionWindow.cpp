//
//
//

#include "../includes/optionWindow.hpp"
#include "../includes/mainWindow.hpp"

OptionWindow::OptionWindow(QWidget *parent): QWidget(parent)
{
   settings_ = new UISettings();

   button_save = new QPushButton("Ok", this);

   QGridLayout *mainLayout = new QGridLayout;

   mainLayout->addWidget(colorGroupBox(), 0, 0, 1, 2);
   mainLayout->addWidget(backgroundColorGroupBox(), 1, 0, 1, 2);
   mainLayout->addWidget(WidgetImage(), 2, 0, 1, 2);
   mainLayout->addWidget(fontGroupBox(), 3, 0, 1, 2);
   mainLayout->addWidget(windowSizeGroupBox(), 4, 0, 1, 2);
   mainLayout->addWidget(button_save, 5, 1);
   setLayout(mainLayout);
   setWindowTitle(tr("Settings"));

   QObject::connect(button_save, SIGNAL (released()), this, SLOT (quitter()));

}

OptionWindow::~OptionWindow()
{
   delete button_save;
   delete button_cancel;
}

void OptionWindow::quitter()
{
   this->~OptionWindow();
}

void OptionWindow::updateSize()
{
   this->width = slider->value();
   this->height = slidervert->value();
   
   mainwindow->updateWindowSize(this->width, this->height);
}

QGroupBox *OptionWindow::windowSizeGroupBox()
{
   QGroupBox *sizeGroup = new QGroupBox(tr("Window's size"));
   slider = new QSlider(Qt::Horizontal);
   slidervert = new QSlider(Qt::Horizontal);
   QLabel *horLabel = new QLabel(tr("width"));
   QLabel *verLabel = new QLabel(tr("height"));
   QPushButton *setSize = new QPushButton(tr("set size"));
   slider->setTickPosition(QSlider::TicksBothSides);
   slidervert->setTickPosition(QSlider::TicksBothSides);
   slider->setTickInterval(1);
   slidervert->setTickInterval(1);
   slider->setMinimum(0);
   slidervert->setMinimum(0);
   slider->setMaximum(10);
   slidervert->setMaximum(10);
   slider->setValue(settings_->getWidth());
   slidervert->setValue(settings_->getHeight());

   QVBoxLayout *sizeLayout = new QVBoxLayout;

   sizeLayout->addWidget(horLabel);
   sizeLayout->addWidget(slider);
   sizeLayout->addWidget(verLabel);
   sizeLayout->addWidget(slidervert);
   sizeLayout->addWidget(setSize);

   sizeGroup->setLayout(sizeLayout);

   QObject::connect(setSize, SIGNAL(released()), this, SLOT(updateSize()));

   return sizeGroup;
}

QGroupBox *OptionWindow::WidgetImage()
{
   QGroupBox *WidgetGroup = new QGroupBox(tr("Widget's Background Picture"));

   message_button = new QPushButton("Background image for message", this);
   contact_button = new QPushButton("Background image for contact list", this);
   text_button = new QPushButton("Background image for text zone", this);

   WidgetGroup->setCheckable(true);
   WidgetGroup->setChecked(true);
   QVBoxLayout *imageLayout = new QVBoxLayout;

   imageLayout->addWidget(message_button);
   imageLayout->addWidget(contact_button);
   imageLayout->addWidget(text_button);

   WidgetGroup->setLayout(imageLayout);

   QObject::connect(message_button, SIGNAL (released()), this, SLOT (imageMessages()));
   QObject::connect(contact_button, SIGNAL (released()), this, SLOT (imageContact()));
   QObject::connect(text_button, SIGNAL (released()), this, SLOT (imageText()));

   return WidgetGroup;
}

QGroupBox *OptionWindow::fontGroupBox()
{
   QGroupBox *fontGroup = new QGroupBox(tr("Font Style and Size"));
   QComboBox *style = new QComboBox(this);
   QSpinBox *size = new QSpinBox(this);
   QVBoxLayout *fontLayout = new QVBoxLayout;
   QPushButton *setFont = new QPushButton(tr("set font size"));

   size->setValue(15);

   fontLayout->addWidget(style);
   fontLayout->addWidget(size);
   fontLayout->addWidget(setFont);

   fontGroup->setLayout(fontLayout);

   //QObject::connect(setFont, SIGNAL(released()), this, SLOT(setFontSize()));

   return fontGroup;
}

//void OptionWindow::setFontSize()
//{
//   this->fontSize = size->value();
//   settings_->setSize(this->fontSize);
//}

QGroupBox *OptionWindow::backgroundColorGroupBox()
{
   QGroupBox *backgroundGroup = new QGroupBox(tr("Background Color"));
   backgroundButton = new QPushButton();
   QVBoxLayout *backgroundLayout = new QVBoxLayout;

   backgroundLayout->addWidget(backgroundButton);

   backgroundGroup->setLayout(backgroundLayout);

   QObject::connect(backgroundButton, SIGNAL (released()), this, SLOT (colorBack()));

   return backgroundGroup;
}

QGroupBox *OptionWindow::colorGroupBox()
{
   QGroupBox *colorGroup = new QGroupBox(tr("Buttons Color"));
   QPushButton *button_col_send = new QPushButton("Send Button", this);
   QPushButton *button_col_call = new QPushButton("Call Button", this);
   QPushButton *button_col_add = new QPushButton("Add Button", this);
   QVBoxLayout *color_layout = new QVBoxLayout;

   color_layout->addWidget(button_col_send);
   color_layout->addWidget(button_col_call);
   color_layout->addWidget(button_col_add);
   color_layout->addStretch(1);
   colorGroup->setLayout(color_layout);

   QObject::connect(button_col_send, SIGNAL (released()), this, SLOT (colorSend()));
   QObject::connect(button_col_call, SIGNAL (released()), this, SLOT (colorCall()));
   QObject::connect(button_col_add, SIGNAL (released()), this, SLOT (colorAdd()));

   return colorGroup;
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

void OptionWindow::imageMessages()
{
    QString file = QFileDialog::getOpenFileName(this, "Open an Image", QString(), "Images (*.png *.jpg *.jpeg)");
    if (QFile(file).exists())
        mainwindow->updateMessageBox(file);
}

void OptionWindow::imageContact()
{
    QString file = QFileDialog::getOpenFileName(this, "Open an Image", QString(), "Images (*.png *.jpg *.jpeg)");
/*   QFileDialog dialog(this);
   dialog.setFileMode(QFileDialog::AnyFile);
   dialog.setNameFilter(tr("Images (*.png *.jpg)"));
   dialog.setViewMode(QFileDialog::Detail);*/
    if (QFile(file).exists())
      mainwindow->updateContactBox(file);
}

void OptionWindow::imageText()
{
    QString file = QFileDialog::getOpenFileName(this, "Open an Image", QString(), "Images (*.png *.jpg *.jpeg)");
    if (QFile(file).exists())
        mainwindow->updateTextBox(file);
}

void OptionWindow::colorBack()
{
   QColor color = QColorDialog::getColor(Qt::yellow, this );
   if( color.isValid() )
   {
      qDebug() << "Color Choosen : " << color.name();
      mainwindow->updateMainColor(color.name());
      QString qss = QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color.name());
      backgroundButton->setStyleSheet(qss);
   }  
}

void OptionWindow::colorSend()
{
   QColor color = QColorDialog::getColor(Qt::yellow, this );
   if( color.isValid() )
   {
      mainwindow->updateButtonSend(color.name());
      qDebug() << "Color Choosen : " << color.name();
      QString qss = QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color.name());
   }
}

void OptionWindow::colorCall()
{
   QColor color = QColorDialog::getColor(Qt::yellow, this );
   if( color.isValid() )
   {
      mainwindow->updateButtonCall(color.name());
      qDebug() << "Color Choosen : " << color.name();
      QString qss = QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color.name());
   }
}

void OptionWindow::colorAdd()
{
   QColor color = QColorDialog::getColor(Qt::yellow, this );
   if( color.isValid() )
   {
      mainwindow->updateButtonAdd(color.name());
      qDebug() << "Color Choosen : " << color.name();
      QString qss = QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color.name());
   }
}