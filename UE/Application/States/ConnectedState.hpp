#pragma once

#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleDisconnected();
    void handleReceivingSms(const common::PhoneNumber senderNumber , const std::string& text);

};

}
