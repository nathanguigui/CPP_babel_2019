//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_OUTPUTDEVICE_HPP
#define CPP_BABEL_2019_OUTPUTDEVICE_HPP

#include <portaudio.h>
#include <client/includes/Mutex/Mutex.hpp>
#include <client/includes/Audio/AudioException.hpp>
#include "IAudioDevice.hpp"

class OutputDevice : public IAudioDevice {
public:
    OutputDevice();
    ~OutputDevice();

    void setOnSoundDeviceEventListener(IAudioDevice::listeningDevice *) {};

    void startStream() override;

    void stopStream() override;

    IAudioDevice &operator<<(const AudioSettings::Decoded &soundBuffer);

private:
    OutputDevice(const OutputDevice&) = default;
    const OutputDevice &operator=(const OutputDevice &) {return *this;};
    void initOutputDevice();

    IAudioDevice &operator>>(AudioSettings::Decoded &soundBuffer);
    static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

    std::list<AudioSettings::Decoded> buffers;
    PaStreamParameters outputParameters;
    PaStream *stream;
    Mutex mutex;
    bool isRunning;
};

#endif //CPP_BABEL_2019_OUTPUTDEVICE_HPP
