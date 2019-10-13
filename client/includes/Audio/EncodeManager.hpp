//
// Created by guigui on 10/12/19.
//

#ifndef CPP_BABEL_2019_ENCODEMANAGER_HPP
#define CPP_BABEL_2019_ENCODEMANAGER_HPP

#include "AudioSettings.hpp"
#include "client/includes/Audio/AudioException.hpp"

class EncodeManager {
public:
    EncodeManager();
    ~EncodeManager();

    AudioSettings::Encoded encode(const AudioSettings::Decoded &sound);
    AudioSettings::Decoded decode(const AudioSettings::Encoded &sound);

private:
    EncodeManager(const EncodeManager &) {};
    const EncodeManager &operator=(const EncodeManager &) {return *this;};

    OpusDecoder *decoder;
    OpusEncoder *encoder;
};

#endif //CPP_BABEL_2019_ENCODEMANAGER_HPP
