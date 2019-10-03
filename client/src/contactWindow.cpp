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
    buttonQuit = new QPushButton("Quit", this);
    contactList = new QListWidget();

    QGridLayout *contactLayout = new QGridLayout;

    contactLayout->addWidget(buttonAdd, 1, 0);
    contactLayout->addWidget(contactList, 0, 0, 1, 2);
    contactLayout->addWidget(buttonQuit, 1, 1);

    contactLayout->setHorizontalSpacing(20);
    contactLayout->setVerticalSpacing(20);
    contactLayout->setContentsMargins(20, 20, 20, 20);

    contactList->setStyleSheet(settings_->getContact());
    this->setStyleSheet(settings_->getMainWindow());

    setLayout(contactLayout);
    setWindowTitle(tr("add contact"));

    QObject::connect(buttonQuit, SIGNAL(released()), this, SLOT (quitter()));
    QObject::connect(buttonAdd, SIGNAL(released()), this, SLOT (addContact()));
}

ContactWindow::~ContactWindow()
{
    delete buttonAdd;
    delete contactList;
}

void ContactWindow::quitter()
{
    this->~ContactWindow();
}

void ContactWindow::addContact()
{
    if (contactChosen != NULL) {
        QListWidgetItem *it = contactList->takeItem(contactList->currentRow());
        mainwindow->addNewContact(contactChosen.toStdString(), "1.1.1.1", true);
        delete it;
    }
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

void ContactWindow::fillList(std::vector<std::string> contact)
{
    int i = 0;
    while (i < contact.size())
    {
        QString str = QString::fromUtf8(contact[i].c_str());
        contactList->addItem(str);
        i++;
    }
   QObject::connect(contactList, SIGNAL (itemClicked(QListWidgetItem*)), this, SLOT (contactClicked(QListWidgetItem*)));
}

void ContactWindow::contactClicked(QListWidgetItem *item)
{
    contactChosen = item->text();
}

