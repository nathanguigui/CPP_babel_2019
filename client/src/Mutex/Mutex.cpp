//
// Created by guigui on 10/12/19.
//

#include "Mutex/Mutex.hpp"

void Mutex::lock() {
    this->mutex.lock();
}

bool Mutex::tryLock(int ms) {
    return this->mutex.tryLock(ms);
}

void Mutex::unlock() {
    this->mutex.unlock();
}
