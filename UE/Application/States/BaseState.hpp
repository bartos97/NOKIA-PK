#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleSendingSms(common::PhoneNumber nr, std::string text) override;
    void handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text) override;
    void handleReceivingCall(common::PhoneNumber callingPhoneNumber) override;
    void handleSendingCallAccept(common::PhoneNumber callingPhoneNumber) override;
    void handleSendingCallDropped(common::PhoneNumber callingPhoneNumber) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
