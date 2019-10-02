//
//
//

#include "../includes/contactWindow.hpp"
#include "../includes/mainWindow.hpp"
#include "../includes/optionWindow.hpp"

ContactWindow::ContactWindow(QWidget *parent): QWidget(parent)
{
    settings_ = new UISettings();

    buttonAdd = new QPushButton("Add contact", this);
    contactList = new QListWidget();

    QGridLayout *contactLayout = new QGridLayout;

    contactLayout->addWidget(buttonAdd, 1, 0);
    contactLayout->addWidget(contactList, 0, 0);

    contactLayout->setHorizontalSpacing(20);
    contactLayout->setVerticalSpacing(20);
    contactLayout->setContentsMargins(20, 20, 20, 20);

    contactList->setStyleSheet(settings_->getContact());
    this->setStyleSheet(settings_->getMainWindow());

    setLayout(contactLayout);
    setWindowTitle(tr("add contact"));

    QObject::connect(buttonAdd, SIGNAL(released()), this, SLOT (addContact()));
}

ContactWindow::~ContactWindow()
{
    delete buttonAdd;
    delete contactList;
}

void ContactWindow::addContact()
{
    this->~ContactWindow();
}

void ContactWindow::centerAndResize()
{
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   width *= 0.2;
   height *= 0.5;
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

