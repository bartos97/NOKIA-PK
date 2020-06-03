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
    void handleSendingSms(common::PhoneNumber nr, std::string text);
    void handleReceivingCall(common::PhoneNumber callingPhoneNumber);
    void handleSendingCallAccept(common::PhoneNumber callingPhoneNumber);
    void handleSendingCallDropped(common::PhoneNumber callingPhoneNumber);
};

}
