//
// Created by guigui on 9/17/19.
//

#include <client/includes/Network/SERVER_IP.hpp>
#include "mainWindow.hpp"
#include "Network/SessionManager.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

/// Constructor for main widget
MainWindow::MainWindow(QWidget *parent): QWidget(parent), registerOk(false)
{
	qRegisterMetaType<std::vector<ContactDetails>>("stdVectorContact");
	qRegisterMetaType<std::string>("stdString");

	/// Settings
	settings_ = new UISettings();

	/// button
	button_contact_ = new QPushButton("Add contact", this);
	button_send_ = new QPushButton("Send", this);
	button_call_ = new QPushButton("Call", this);

	/// text box
	textBox_  = new QTextEdit();

	/// list view
	list_ = new QListWidget();
	list_messages_ = new QListWidget();

	/// com contact
	contact_name_ = new QLabel();

	QAction *quitter = new QAction("&Quit", this);
	QAction *deconnexion = new QAction("&Disconnect", this);
	QAction *reload = new QAction("&Reload", this);
	QAction *options = new QAction("&Options", this);


	/// ToolBar object
	toolbar_ = new QToolBar();
	toolbar_->addAction(options);
	toolbar_->addAction(deconnexion);
	toolbar_->addAction(reload);
	toolbar_->addAction(quitter);
	toolbar_->setOrientation(Qt::Horizontal);
	QBoxLayout *toolLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	toolLayout->setContentsMargins(0, 0, 0, 0);
	toolLayout->addWidget(toolbar_);

	setAllContact();

	connect(quitter, &QAction::triggered, this, &MainWindow::quit);
	connect(deconnexion, &QAction::triggered, this, &MainWindow::disconnectLogin);
	connect(reload, &QAction::triggered, this, &MainWindow::reload);
	connect(options, &QAction::triggered, this, &MainWindow::showOptions);

	QGridLayout *mainLayout = new QGridLayout;
	toolLayout->addLayout(mainLayout);
	mainLayout->setHorizontalSpacing(20);
	mainLayout->setVerticalSpacing(20);
	mainLayout->setContentsMargins(20, 20, 20, 20);
	mainLayout->addWidget(contact_name_,0, 3);
	mainLayout->addWidget(button_contact_,14, 7, 1, 3);
	mainLayout->addWidget(button_send_, 13, 6);
	mainLayout->addWidget(button_call_, 14, 6);
	mainLayout->addWidget(list_messages_, 1, 0, 12, 7);
	mainLayout->addWidget(textBox_, 13, 0, 2, 6);
	mainLayout->addWidget(list_, 0, 7, 14, 3);
	toolbar_->setStyleSheet("background-color: rgb(255,255,255);");

	this->setStyleSheet(settings_->getMainWindow());
	button_send_->setStyleSheet(settings_->getButtonSend());
	button_contact_->setStyleSheet(settings_->getButtonAdd());
	button_call_->setStyleSheet(settings_->getButtonCall());
	textBox_->setStyleSheet(settings_->getText());
	list_messages_->setStyleSheet(settings_->getMessage());
	list_->setStyleSheet(settings_->getContact());
	contact_name_->setStyleSheet(settings_->getLabel());
	setLayout(mainLayout);
	setWindowTitle(tr("BABEL"));

	connect(&this->asyncSession, SIGNAL(RegisterDone()), this, SLOT(handleAuthCompleted()));
	QObject::connect(&this->asyncSession, SIGNAL (UpdateDone(std::vector<ContactDetails>)), &contactWindow, SLOT(fillList(std::vector<ContactDetails>)));
	QObject::connect(&this->asyncSession, SIGNAL (InfoDone(std::vector<ContactDetails>)), this, SLOT(importContact(std::vector<ContactDetails>)));	
	QObject::connect(&this->asyncSession, SIGNAL (InvitedRinging(std::string, std::string, int)), this, SLOT (incomingCall(std::string, std::string, int)));

	//QObject::connect(callManager, SIGNAL (callTerminated()), &this->duringCall, SLOT (quit()));

	QObject::connect(button_contact_, SIGNAL (released()), this, SLOT (addContact()));
	QObject::connect(button_send_, SIGNAL(released()), this, SLOT(sendMessage()));
	QObject::connect(button_call_, SIGNAL(released()), this, SLOT(call()));
	QObject::connect(list_, SIGNAL (itemClicked(QListWidgetItem*)), this, SLOT (setName(QListWidgetItem*)));
}

// Destructor
MainWindow::~MainWindow()
{
	delete toolbar_;
	delete settings_;
	delete textBox_;
	delete button_contact_;
	delete button_send_;
	delete button_call_;
	delete list_messages_;
	delete list_;
	//this->duringCall.quit();
	this->asyncSession.quit();
}

void MainWindow::setName(QListWidgetItem *item)
{
	qDebug() << "Login = " << item->text();
	contact_name_->setText(item->text());
	printAllMessages();
}

void MainWindow::reload()
{
    asyncSession.asyncInfo();
}

void MainWindow::importContact(std::vector<ContactDetails> details)
{
    std::vector<ContactDetails>::const_iterator it;
    qDebug() << "Import Contact";
    for (it = details.begin(); it != details.end(); it++) {
        qDebug() << "New Contact : " << QString::fromStdString(it->name);
		if (contact_list.find(QString::fromStdString(it->name)) == contact_list.end()) {
        	addNewContact(it->name, it->ip, it->connected);
		} else {
			contact_list[QString::fromStdString(it->name)]->setState(it->connected);
			contact_list[QString::fromStdString(it->name)]->setIp(QString::fromStdString(it->ip));
		}
	}
    qDebug() << "End Import";
    setAllContact();
}

void MainWindow::setAllContact()
{
    list_->clear();
    std::map<QString, contact *>::iterator itr;
    for (itr = contact_list.begin(); itr != contact_list.end(); itr++) {
    	QListWidgetItem *item = new QListWidgetItem(list_);
    	item->setText(QString(itr->first));
      	if (itr->second->getState() == true)
        	item->setBackground(Qt::green);
      	else
         	item->setBackground(Qt::red);      
      	list_->addItem(item);
      	item->setSizeHint(QSize(item->sizeHint().width(), 30));
   }
}

void MainWindow::addNewContact(std::string login, std::string ip, bool state) {
    contact *newContact = new contact(QString::fromStdString(login), QString::fromStdString(ip), state);
    contact_list.insert( {QString::fromStdString(login), new contact(QString::fromStdString(login), QString::fromStdString(ip), state) });
    contact_list.find(QString::fromStdString(login))->second->setMainWindow(this);
    setAllContact();
    qDebug() << "Added Contact : " << QString::fromStdString(login);
}

void MainWindow::quit()
{
	this->asyncSession.asyncBye();
	this->asyncSession.quit();
	this->duringCall.quit();   
	qApp->quit();
}

QString MainWindow::disconnectLogin()
{
	this->asyncSession.asyncBye();
}

QString MainWindow::launchlogin()
{
	this->asyncSession.asyncInfo();
	QInputDialog *log = new QInputDialog(this);
	log->setLabelText(tr("Enter login: "));
	log->setWindowTitle(tr("Login"));
	log->adjustSize();
	log->setStyleSheet("background-color: rgb(255, 255, 255);");
	log->move(QApplication::desktop()->screen()->rect().center() - log->rect().center());
	if (log->exec() == QDialog::Accepted) {
      	login = log->textValue();
   	}
   	else
       	return ("NULL");
   	qDebug() << login;
   	auto host = std::string(SERVER_IP);
   	std::string device = "perceval";
   	std::string callId = "guigui";
   	this->asyncSession.delayRun(host, 25565, login.toStdString(), device, callId);
   	this->asyncSession.asyncRegister();
   	return login;
}

void MainWindow::incomingCall(std::string name, std::string ip, int port)
{
	//qDebug() << "appel entrant";
    QString login = QString::fromStdString(name);
   	QMessageBox *incoming = new QMessageBox();
   	QString message = QString("%1 is calling you ").arg(login);
   	incoming->setText(message);
   	incoming->setStandardButtons(QMessageBox::Yes | QMessageBox::Ignore);
   	incoming->setDefaultButton(QMessageBox::Yes);

   	int ret = incoming->exec();
	callManager = new CallManager(this->asyncSession);

   	switch (ret) {
      	case QMessageBox::Yes:
		  	emit InvitedAccepted(login.toStdString());
			callManager->joinCall(name, ip, port);
			duringCall.doCall();
         	return;
      	case QMessageBox::Ignore:
			callManager->declineCall(name);
         	return;
   }
}

void MainWindow::addContact()
{
   	contactWindow.setMainWindow(this);
   	contactWindow.centerAndResize();
   	this->asyncSession.asyncUpdate();
   	contactWindow.show();
}

void MainWindow::sendMessage()
{
    QString message;
    message = this->textBox_->toPlainText();
    if (message == "")
        return;
    if (contact_name_->text() != QString::null) {
        contact_list.find(contact_name_->text())->second->addMessage(message.toStdString(), 0);
        updateMessage();
    }
    qDebug() << message;
    this->textBox_->clear();
}

void MainWindow::printAllMessages()
{
    list_messages_->clear();
    std::vector<QString> messages = contact_list.find(contact_name_->text())->second->getMessages();
    for (auto i = messages.begin(); i != messages.end(); i++)
       list_messages_->addItem(*i);

}

void MainWindow::updateMessage()
{
   	std::vector<QString> messages = contact_list.find(contact_name_->text())->second->getMessages();
   	auto i = messages.rbegin();
   	list_messages_->addItem(*i);
}

void MainWindow::addMessageFromContact(std::string login, std::string message)
{
    contact_list.find(contact_name_->text())->second->addMessage(message, 1);
    if (contact_name_->text() == QString::fromStdString(login))
        updateMessage();
}

void MainWindow::call()
{

   	if (contact_name_->text() == QString::null || contact_list[contact_name_->text()]->getState() == false)
		return;
	CallManager *callManager = new CallManager(this->asyncSession);
	std::string tmp = contact_name_->text().toStdString();
	callManager->makeCall(tmp);
	duringCall.doCall();
	//connect(&duringCall, SIGNAL(endCall()), &contactWindow, SLOT (quitter()));
	//CallWindow *callWindow = new CallWindow();
	//callWindow->setMainWindow(this);
	//callWindow->centerAndResize();
	//callWindow->show();
    //contact_list.find(contact_name_->text())->second->addMessage("Ceci est un message test envoyé",1);
    //updateMessage();
	//incomingCall(contact_name_->text().toStdString());
    qDebug() << "make a call";
}

void MainWindow::launchSplashScreen()
{
   	QSize availableSize = qApp->desktop()->availableGeometry().size();
   	int width = availableSize.width();
   	int height = availableSize.height();
   	QMovie *splash = new QMovie("../templates/cube.gif");
   	QLabel *processLabel = new QLabel(this);
   	if (!splash->isValid())
      	std::cout << "file error" << std::endl;
   	processLabel->resize(width * float(settings_->getWidth() * 10.0), height * float(settings_->getHeight()) * 10.0);
   	processLabel->setStyleSheet("background-color: rgb(38,38,38);");
   	processLabel->setWindowFlags(Qt::FramelessWindowHint);
   	processLabel->setAlignment(Qt::AlignCenter);
   	processLabel->setMovie(splash);
   	processLabel->show();
   	splash->start();
   	QTimer::singleShot(3500, processLabel, SLOT(close()));
   	QTimer::singleShot(0, this, SLOT(show()));
}

void MainWindow::centerAndResize()
{
	QSize availableSize = qApp->desktop()->availableGeometry().size();
   	int width = availableSize.width();
   	int height = availableSize.height();
   	width *= float(settings_->getWidth() / 10.0);
   	height *= float(settings_->getHeight() / 10.0);
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

void MainWindow::updateWindowSize(int width, int height) {
   	settings_->setHeight(height);
   	settings_->setWidth(width);
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int newWidth = availableSize.width();
    int newHeight = availableSize.height();
    newWidth *=  float(settings_->getWidth() / 10.0);
    newHeight *= float(settings_->getHeight() / 10.0);
    QSize newSize( newWidth, newHeight );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
    );
}

void MainWindow::updateActiveImage(int value) {
    settings_->setActiveImage(value);
    list_messages_->setStyleSheet(settings_->getMessage());
    list_->setStyleSheet(settings_->getContact());
    textBox_->setStyleSheet(settings_->getText());
}

void MainWindow::showOptions()
{
   	OptionWindow *options = new OptionWindow();
   	options->setMainWindow(this);
   	options->centerAndResize();
   	options->show();
}

void MainWindow::handleAuthCompleted() {
    auto tmp = std::string("auth detected in mainwond\n");
    qDebug() << tmp.c_str();
}

#pragma GCC diagnostic pop