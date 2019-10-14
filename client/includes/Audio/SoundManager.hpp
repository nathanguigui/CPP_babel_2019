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
#include <QtCore/QTextStream>
#include <QWidget>

Q_DECLARE_METATYPE(IAudioDevice*)

class SoundManager : public QObject, public IAudioDevice::listeningDevice {
    Q_OBJECT
public:
    SoundManager();
    ~SoundManager() override;
    void startRecording();
    void stopRecording();
    void startPlaying();
    void stopPlaying();

    void playSound(AudioSettings::Encoded sound);
public slots:
    void onSoundAvailable(IAudioDevice *device) override;

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
