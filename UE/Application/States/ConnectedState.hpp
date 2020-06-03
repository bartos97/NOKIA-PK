#pragma once

#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleReceivingSms(common::PhoneNumber senderNumber , const std::string& text) override;

    // IUserEventsHandler interface
    void handleSendingSms(common::PhoneNumber nr, std::string text) override;
    void handleSendingCallRequest(common::PhoneNumber receiver) override;
    void handleSendingCallDrop(common::PhoneNumber receiver) override;
    void handleReceivingCallAccept(common::PhoneNumber converserNumber) override;
    void handleReceivingCallDropped(common::PhoneNumber converserNumber) override;
    void handleUnknownReceiver() override;
};

}
