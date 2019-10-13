//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_AUDIOEXCEPTION_HPP
#define CPP_BABEL_2019_AUDIOEXCEPTION_HPP
#include <stdexcept>

class AudioException : public std::runtime_error {
public:
    /// Default ctor
    explicit AudioException(const std::string &err);

    /// Default dtor
    ~AudioException() noexcept override = default;

    /// Override what
    const char *what() const noexcept override;

private:
    std::string message;
};

#endif