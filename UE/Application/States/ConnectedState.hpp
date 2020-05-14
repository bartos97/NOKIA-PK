#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleDisconnected();
    void handleReceivingSms(int from ,const std::string& text);
    void handleSendingSms(common::PhoneNumber nr, std::string text);

};

}
