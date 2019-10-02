//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_AUDIODEVICE_HPP
#define CPP_BABEL_2019_AUDIODEVICE_HPP

#include "AudioSettings.hpp"

class IAudioDevice {
public:
    /// Start the stream
    virtual void startStream() = 0;
    /// Stop the stream
    virtual void stopStream() = 0;
    class listeningDevice {
    public:
        /// Function called when the sound is available
        virtual void onSoundAvailable(IAudioDevice *audioDevice) = 0;
    };
    virtual IAudioDevice &operator<<(const AudioSettings::Decoded &soundBuffer) = 0;
    virtual IAudioDevice &operator>>(AudioSettings::Decoded &soundBuffer) = 0;
};

#endif //CPP_BABEL_2019_AUDIODEVICE_HPP
