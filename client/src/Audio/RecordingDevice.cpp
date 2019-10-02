//
// Created by guigui on 9/25/19.
//

#include "Audio/RecordingDevice.hpp"

RecordingDevice::RecordingDevice() : stream(nullptr), isRunning(false), listeningDevice(nullptr) {
    if (Pa_Initialize() != paNoError)
        throw AudioException("Pa_Initialize failed");
    this->streamParameters.device = Pa_GetDefaultInputDevice();
    if (this->streamParameters.device == paNoDevice)
        throw AudioException("Pa_GetDefaultInputDevice failed");
    this->streamParameters.channelCount = AudioSettings::NB_CHANNELS;
    this->streamParameters.sampleFormat = paFloat32;
    this->streamParameters.suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->defaultLowInputLatency;
    this->streamParameters.hostApiSpecificStreamInfo = nullptr;
};

RecordingDevice::~RecordingDevice() {
    this->stopStream();
    Pa_Terminate();
}

void RecordingDevice::startStream() {
    if (!this->isRunning) {
        if (Pa_OpenStream(&this->stream, &this->streamParameters, nullptr,
                AudioSettings::SAMPLE_RATE, AudioSettings::FRAMES_PER_BUFFER, paClipOff,
                RecordingDevice::callback, this) != paNoError)
            throw AudioException("Pa_OpenStream failed");
        if (Pa_StartStream(this->stream) != paNoError)
            throw AudioException("Pa_StartStream failed");
        this->isRunning = true;
    }
}

void RecordingDevice::stopStream() {
    if (this->isRunning) {
        if (Pa_CloseStream(this->stream) != paNoError)
            throw AudioException("Pa_CloseStream failed");
        this->isRunning = false;
    }
}

int	RecordingDevice::callback(const void *inputBuffer, void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data) {
    RecordingDevice *obj = reinterpret_cast<RecordingDevice *>(data);
    {
        obj->mutex.lock();
        AudioSettings::Decoded sound;
        sound.size = framesPerBuffer * AudioSettings::NB_CHANNELS;
        sound.buffer.assign(reinterpret_cast<const float *>(inputBuffer), reinterpret_cast<const float *>(inputBuffer) + framesPerBuffer * AudioSettings::NB_CHANNELS);
        obj->soundBuffer.push_back(sound);
    }
    if (obj->listeningDevice)
        obj->listeningDevice->onSoundAvailable(obj);
    return paContinue;
}

void RecordingDevice::setListeningDevice(IAudioDevice::listeningDevice *listeningDevice) {
    RecordingDevice::listeningDevice = listeningDevice;
}

IAudioDevice &RecordingDevice::operator<<(const AudioSettings::Decoded &soundBuffer) {
    return *this;
}

IAudioDevice &RecordingDevice::operator>>(AudioSettings::Decoded &soundBuffer) {
    this->mutex.lock();

    if (!this->soundBuffer.empty()) {
        AudioSettings::Decoded audioCpy = this->soundBuffer.front();
        soundBuffer.buffer = audioCpy.buffer;
        soundBuffer.size = audioCpy.size;
        this->soundBuffer.pop_front();
    } else
        soundBuffer.size = 0;
    return *this;
};
