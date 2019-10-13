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
        explicit callThread(QObject *parent = nullptr);
        ~callThread() override = default;
        
    signals:
        void launchCall();
        void endCall();

    public slots:
        void quit();
        void doCall();

    protected:
        void run() override;

    private:
        bool m_ready;
};

#endif