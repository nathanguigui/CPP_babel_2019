//
// Created by guigui on 10/12/19.
//

#include <client/includes/Mutex/ScopedLock.hpp>

ScopedLock::ScopedLock(IMutex *iMutex) : mutex(iMutex) {
    this->mutex->lock();
}

ScopedLock::~ScopedLock() {
    this->mutex->unlock();
}