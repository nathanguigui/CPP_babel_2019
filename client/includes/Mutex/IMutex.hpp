//
// Created by guigui on 10/12/19.
//

#ifndef CPP_BABEL_2019_IMUTEX_HPP
#define CPP_BABEL_2019_IMUTEX_HPP

class IMutex {
public:
    virtual ~IMutex() = default;
    virtual void lock() = 0;
    virtual bool tryLock(int ms) = 0;
    virtual void unlock() = 0;
};

#endif //CPP_BABEL_2019_IMUTEX_HPP
