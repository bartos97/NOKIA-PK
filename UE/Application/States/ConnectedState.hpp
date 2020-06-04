#pragma once

#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    explicit ConnectedState(Context& context);

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text) override;
    void handleReceivingCallRequest(common::PhoneNumber callingPhoneNumber) override ;

    // IUserEventsHandler interface
    void handleSendingSms(common::PhoneNumber nr, std::string text) override;
    void handleSendingCallRequest(common::PhoneNumber receiver) override;
    void handleSendingCallDrop(common::PhoneNumber receiver) override;
    void handleReceivingCallAccept(common::PhoneNumber callingPhoneNumber) override;
    void handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber) override;
    void handleUnknownReceiver() override;
    void handleSendingCallAccept(common::PhoneNumber callingPhoneNumber) override;
};

}
