//
// Created by guigui on 10/11/19.
//

#include "CallManagement/CallManager.hpp"

CallManager::CallManager(AsyncSession &session) : session(session) {

}

void CallManager::makeCall(std::string &name) {
    this->session.asyncInvite(name, 123);
}
