//
// Created by guigui on 9/25/19.
//

#include "Audio/SoundManager.hpp"

SoundManager::SoundManager() : inputDevice(nullptr), outputDevice(nullptr), recordEnabled(false), playEnabled(false) {
    this->inputDevice = new RecordingDevice;
    this->inputDevice->setListeningDevice(this);
    this->outputDevice = new OutputDevice;
}

SoundManager::~SoundManager() {
    delete this->inputDevice;
    delete this->outputDevice;
}

void SoundManager::playSound(const AudioSettings::Encoded &sound) {
    *this->outputDevice << this->encodeManager.decode(sound);
}

void SoundManager::onSoundAvailable(IAudioDevice *device) {
    AudioSettings::Decoded sound;
    *this->inputDevice >> sound;
    if (sound.size)
        emit soundAvailable(this->encodeManager.encode(sound));
}

void SoundManager::startRecording() {
    this->inputDevice->startStream();
}

void SoundManager::stopRecording() {
    this->inputDevice->stopStream();
}

void SoundManager::startPlaying() {
    this->outputDevice->startStream();
}

void SoundManager::stopPlaying() {
    this->outputDevice->stopStream();
}
