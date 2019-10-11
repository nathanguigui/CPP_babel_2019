//
// Created by guigui on 10/11/19.
//

#ifndef CPP_BABEL_2019_CALLMANAGER_HPP
#define CPP_BABEL_2019_CALLMANAGER_HPP

#include "Network/AsyncSession.hpp"

class CallManager {
public:
    CallManager(AsyncSession &session);
    void makeCall(std::string &name);
    ~CallManager() = default;

private:
    AsyncSession &session;
};

#endif //CPP_BABEL_2019_CALLMANAGER_HPP
