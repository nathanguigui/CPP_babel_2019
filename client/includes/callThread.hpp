//
// headers
//

#ifndef CALLTHREAD_H_
#define CALLTHREAD_H_

#include "callWindow.hpp"
#include <QThread>

class callThread : public QThread {
    Q_OBJECT

    public:
        callThread(QObject *parent = 0);
        void doCall();

    signals:
        void launchCall();
        void endCall();

    protected:
        void run() override;

    private:
        CallWindow callwindow;
        bool m_ready;
};

#endif