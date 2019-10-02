//
// Created by guigui on 9/25/19.
//

#include "Audio/AudioException.hpp"

AudioException::AudioException(const std::string &err) : std::runtime_error(err), message(err) {}

const char *AudioException::what() const noexcept {
    return message.c_str();
}