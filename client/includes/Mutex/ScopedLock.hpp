//
// Created by guigui on 10/12/19.
//

#ifndef CPP_BABEL_2019_SCOPEDLOCK_HPP
#define CPP_BABEL_2019_SCOPEDLOCK_HPP

#include "IMutex.hpp"

class ScopedLock {
public:
    explicit ScopedLock(IMutex *iMutex);
    ~ScopedLock();
private:
    IMutex *mutex;
};

#endif //CPP_BABEL_2019_SCOPEDLOCK_HPP
