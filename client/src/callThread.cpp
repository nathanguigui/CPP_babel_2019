//
//
//

#include "callThread.hpp"

callThread::callThread(QObject *parent): m_ready(false) {
    this->start();
    while(!m_ready) msleep(50);
}

void callThread::doCall()
{
    emit launchCall();
}

void callThread::run()
{
    CallWindow callWindow;
    connect(this, SIGNAL(launchCall()), &callWindow, SLOT (setWindow()));
    connect(&callWindow, SIGNAL (endCall()), this, SIGNAL (endCall()));
    m_ready = true;
    exec();
}

