//
//
//

#include "callThread.hpp"

callThread::callThread(QObject *parent): m_ready(false) {
    this->start();
    while(!m_ready) msleep(50);
}

void callThread::doCall(std::string name)
{
    name_ = name;
    emit launchCall(name_);
}

void callThread::run()
{
    connect(this, SIGNAL(launchCall(std::string)), &callWindow, SLOT (setWindow(std::string)));
    connect(&this->callWindow, SIGNAL (endCall()), this, SLOT (quit()));
    m_ready = true;
    exec();
}

void callThread::quit()
{
    emit terminate(name_);
    this->exit();
}

void callThread::receiveQuit()
{
    this->exit();
}

