//
// Created by guigui on 10/11/19.
//

#ifndef CPP_BABEL_2019_CALLMANAGER_HPP
#define CPP_BABEL_2019_CALLMANAGER_HPP

#include "Network/AsyncSession.hpp"
#include "Network/UdpNetwork.hpp"
#include "Audio/SoundManager.hpp"

Q_DECLARE_METATYPE(int)

class CallManager : public QObject {
    Q_OBJECT

    struct SoundPacket {
        int magic_code;
        int64_t timestamp;
        int soundSize;
        char sound[500];
    };

public:
    CallManager(AsyncSession &session);
    void makeCall(std::string &name);
    void joinCall(std::string &name, std::string &ip, int port);
    void declineCall(std::string &name);
    static void manageAudioPacketParsing(std::string input, CallManager *session);
    ~CallManager() = default;

public slots:
    /// Async function to send port to invited
    void asyncServerReady(int port);
    /// Handle people join
    void handlePeopleJoin(const std::string &name);
    /// Handle people left
    void handlePeopleRefuse(const std::string &name);
    /// Send encoded sound to friend
    void sendSound(const AudioSettings::Encoded &sound);
    /// Play sound on audio manager
    void playSound(const AudioSettings::Encoded sound);

signals:
    void callTerminated();

private:
    AsyncSession &session;
    std::string awaitInviteName;
    bool isAwaitingInvite;
    bool serverInited;
    UdpNetwork *socket;
    UdpNetworkMode mode;
    int listeningPort;
    int friendsInCall = 0;
    int friendsPendingResponse = 0;
    SoundManager soundManager;
};

#endif //CPP_BABEL_2019_CALLMANAGER_HPP
