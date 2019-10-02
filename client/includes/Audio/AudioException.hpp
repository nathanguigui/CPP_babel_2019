//
// Created by guigui on 9/25/19.
//

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