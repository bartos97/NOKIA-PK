#pragma once

#include <string>
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendingSms(common::PhoneNumber receiver, std::string content) = 0;
    virtual void handleSendingCallRequest(common::PhoneNumber receiver) = 0;
    virtual void handleSendingCallDrop(common::PhoneNumber receiver) = 0;
    virtual void handleSendingCallAccept(common::PhoneNumber callingPhoneNumber) = 0;
    virtual void handleSendTalkMessage(const std::string) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showNewSms() = 0;
    virtual void showCallingConnected(const common::PhoneNumber callingPhoneNumber) = 0;
    virtual void showCallingDropped(const common::PhoneNumber callingPhoneNumber) = 0;
    virtual void showCallingTimeout() = 0;
    virtual void showUnknownReceiver() = 0;
    virtual void addReceivedSms(const common::PhoneNumber senderNumber, const std::string& text) = 0;
    virtual void showCallRequest(common::PhoneNumber callingPhoneNumber) = 0;
    virtual void showCallView(const std::string) = 0;
};

}
