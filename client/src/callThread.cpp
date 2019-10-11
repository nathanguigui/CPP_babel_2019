//
//
//

#include "callThread.hpp"
#include <QMetaType>

callThread::callThread(QObject *parent): m_ready(false) {
    start();
    while(!m_ready) msleep(50);
}

void callThread::doCall()
{
    emit launchCall();
}

void callThread::run()
{
    CallWindow wdw();
    connect(this, SIGNAL(launchCall()), &callwindow, SLOT (setWindow()));
    connect(&wdw; SIGNAL (endCall()), this, SIGNAL (endCall()));
    m_ready = true;
    exec();
}

