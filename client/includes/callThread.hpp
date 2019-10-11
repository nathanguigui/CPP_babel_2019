//
// headers
//

#ifndef CALLTHREAD_H_
#define CALLTHREAD_H_

#include <QThread>
#include "callWindow.hpp"

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
        bool m_ready;
};

#endif