//
// Created by guigui on 9/25/19.
//

#include <client/includes/Mutex/ScopedLock.hpp>
#include "Audio/OutputDevice.hpp"

OutputDevice::OutputDevice() : stream(nullptr), isRunning(false) {
    if (Pa_Initialize() != paNoError)
        throw AudioException("fail Pa_Initialize");
    this->initOutputDevice();
}

OutputDevice::~OutputDevice() {
    stopStream();
    Pa_Terminate();
}

void OutputDevice::initOutputDevice() {
    this->outputParameters.device = Pa_GetDefaultInputDevice();
	if (this->outputParameters.device == paNoDevice)
		throw AudioException("fail Pa_GetDefaultOutputDevice");
	this->outputParameters.channelCount = AudioSettings::NB_CHANNELS;
	this->outputParameters.sampleFormat = paFloat32;
	this->outputParameters.suggestedLatency = Pa_GetDeviceInfo(this->outputParameters.device)->defaultLowOutputLatency;
	this->outputParameters.hostApiSpecificStreamInfo = nullptr;
}

void OutputDevice::startStream() {
    if (!this->isRunning) {
        if (Pa_OpenStream(&this->stream, nullptr, &this->outputParameters, AudioSettings::SAMPLE_RATE,
                AudioSettings::FRAMES_PER_BUFFER, paClipOff, OutputDevice::callback, this) != paNoError)
            throw AudioException("fail Pa_OpenStream");
        if (Pa_StartStream(this->stream) != paNoError)
            throw AudioException("fail Pa_StartStream");
        this->isRunning = true;
    }
}

void OutputDevice::stopStream() {
    if (this->isRunning) {
        if (Pa_CloseStream(this->stream) != paNoError)
            throw AudioException("fail Pa_StopStream");
        this->isRunning = false;
    }
}

IAudioDevice &OutputDevice::operator<<(const AudioSettings::Decoded &soundBuffer) {
    ScopedLock scopedLock(&this->mutex);
    if (soundBuffer.size) {
        AudioSettings::Decoded soundCpy;
        soundCpy.buffer = soundBuffer.buffer;
        soundCpy.size = soundBuffer.size;
        this->buffers.push_back(soundCpy);
    }
    return *this;
}

IAudioDevice &OutputDevice::operator>>(AudioSettings::Decoded &soundBuffer) {
    return *this;
}

int OutputDevice::callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                           void *userData) {
    auto *obj = reinterpret_cast<OutputDevice *>(userData);
    ScopedLock scopedLock(&obj->mutex);
    if (obj->buffers.empty())
        return paContinue;
    AudioSettings::Decoded sound = obj->buffers.front();
    auto *wptr = static_cast<float *>(outputBuffer);
    for (int i = 0; i < sound.size; i++)
		*wptr++ = sound.buffer[i];
    obj->buffers.pop_front();
    return paContinue;
}
