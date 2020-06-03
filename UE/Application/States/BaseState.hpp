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
    void handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text) override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;

    // IUserEventsHandler interface
    void handleSendingSms(common::PhoneNumber nr, std::string text) override;
    void handleSendingCallRequest(common::PhoneNumber receiver) override;
    void handleReceivingCallAccept(common::PhoneNumber converserNumber) override;
    void handleReceivingCallDropped(common::PhoneNumber converserNumber) override;
    void handleUnknownReceiver() override;
    void handleSendingCallDrop(common::PhoneNumber receiver) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
