//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_SOUNDMANAGER_HPP
#define CPP_BABEL_2019_SOUNDMANAGER_HPP

#include <QtCore/QObject>
#include <client/includes/Audio/OutputDevice.hpp>
#include <client/includes/Audio/RecordingDevice.hpp>
#include "IAudioDevice.hpp"
#include "EncodeManager.hpp"

class SoundManager : public QObject, public IAudioDevice::listeningDevice {
    Q_OBJECT
public:
    SoundManager();
    ~SoundManager() override;

public slots:
    void playSound(const AudioSettings::Encoded &sound);
    void onSoundAvailable(IAudioDevice *device) override;
    void startRecording();
    void stopRecording();
    void startPlaying();
    void stopPlaying();

signals:
    void soundAvailable(const AudioSettings::Encoded &sound);

private:
    SoundManager(const SoundManager &) : QObject() {}
    const SoundManager &operator=(const SoundManager &) {return *this;}

    RecordingDevice *inputDevice;
    OutputDevice *outputDevice;
    EncodeManager encodeManager;
    bool playEnabled;
    bool recordEnabled;
};

#endif //CPP_BABEL_2019_SOUNDMANAGER_HPP
