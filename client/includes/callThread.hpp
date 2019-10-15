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
        void doCall(std::string);
        CallWindow callWindow;
        
    signals:
        void launchCall(std::string);
        void endCall();
        void closeRingWindow();
        void terminate(std::string);

    public slots:
        void quit();
        void receiveQuit();

    protected:
        void run() override;

    private:
        bool m_ready;
        std::string name_;
};

#endif