//
// Created by guigui on 10/12/19.
//

#include "Audio/EncodeManager.hpp"

EncodeManager::EncodeManager() {
    int error;

    this->encoder = opus_encoder_create(AudioSettings::SAMPLE_RATE, AudioSettings::NB_CHANNELS, OPUS_APPLICATION_VOIP, &error);
    if (error != OPUS_OK)
        throw AudioException("fail opus_encoder_create");
    this->decoder = opus_decoder_create(AudioSettings::SAMPLE_RATE, AudioSettings::NB_CHANNELS, &error);
    if (error != OPUS_OK)
        throw AudioException("fail opus_decoder_create");
}

EncodeManager::~EncodeManager() {
    if (this->encoder)
        opus_encoder_destroy(this->encoder);
    if (this->decoder)
        opus_decoder_destroy(this->decoder);
}

AudioSettings::Encoded EncodeManager::encode(const AudioSettings::Decoded &sound) {
    AudioSettings::Encoded encoded;
    encoded.buffer.resize(sound.size);
    encoded.size = opus_encode_float(this->encoder, sound.buffer.data(), AudioSettings::FRAMES_PER_BUFFER, encoded.buffer.data(), sound.size);
    if (encoded.size < 0)
        throw AudioException("fail opus_encode_float");
    return encoded;
}

AudioSettings::Decoded EncodeManager::decode(const AudioSettings::Encoded &sound) {
    AudioSettings::Decoded decoded;
    decoded.buffer.resize(AudioSettings::FRAMES_PER_BUFFER * AudioSettings::NB_CHANNELS);
    decoded.size = opus_decode_float(this->decoder, sound.buffer.data(), sound.size, decoded.buffer.data(), AudioSettings::FRAMES_PER_BUFFER, 0) * AudioSettings::NB_CHANNELS;
    if (decoded.size < 0)
        throw AudioException("fail opus_decode_float");
    return decoded;
}
