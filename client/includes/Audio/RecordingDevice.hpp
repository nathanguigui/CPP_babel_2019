//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_RECORDINGDEVICE_HPP
#define CPP_BABEL_2019_RECORDINGDEVICE_HPP

#include "IAudioDevice.hpp"
#include <portaudio.h>
#include <QMutex>
#include "AudioException.hpp"

class RecordingDevice : public IAudioDevice {
public:
    RecordingDevice();
    ~RecordingDevice() ;
    void startStream() override;
    void stopStream() override;
    void setListeningDevice(IAudioDevice::listeningDevice *listeningDevice);
    static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
    IAudioDevice &operator<<(const AudioSettings::Decoded &soundBuffer) override;
    IAudioDevice &operator>>(AudioSettings::Decoded &soundBuffer) override;
private:
    RecordingDevice(const RecordingDevice &) {}
    const RecordingDevice &operator=(const RecordingDevice &) { return *this; }

    std::list<AudioSettings::Decoded> soundBuffer;
    PaStreamParameters streamParameters;
    PaStream *stream;
    QMutex mutex;
    bool isRunning;
    IAudioDevice::listeningDevice *listeningDevice;
};

#endif //CPP_BABEL_2019_RECORDINGDEVICE_HPP
