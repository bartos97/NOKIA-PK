#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text) override;
    void handleReceivingCall(common::PhoneNumber callingPhoneNumber) override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleSendingSms(common::PhoneNumber nr, std::string text) override;
    void handleSendingCallAccept(common::PhoneNumber callingPhoneNumber) override;
    void handleSendingCallDropped(common::PhoneNumber callingPhoneNumber) override;

private:
    Context context;
    common::PrefixedLogger logger;

};

}
