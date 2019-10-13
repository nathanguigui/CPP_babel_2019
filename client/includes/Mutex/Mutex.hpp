//
// Created by guigui on 10/12/19.
//

#ifndef CPP_BABEL_2019_MUTEX_HPP
#define CPP_BABEL_2019_MUTEX_HPP

#include <QtCore/QMutex>
#include "IMutex.hpp"

class Mutex : public IMutex {
public:
    Mutex() = default;
    ~Mutex() override = default;
    void lock() override;
    bool tryLock(int ms) override;
    void unlock() override;

private:
    QMutex mutex;
};

#endif //CPP_BABEL_2019_MUTEX_HPP
