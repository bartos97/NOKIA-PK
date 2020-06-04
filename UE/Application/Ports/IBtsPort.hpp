#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleDisconnected() = 0;
    virtual void handleReceivingCallAccept(common::PhoneNumber callingPhoneNumber) = 0;
    virtual void handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber) = 0;
    virtual void handleUnknownReceiver() = 0;
    virtual void handleReceivingCallRequest(common::PhoneNumber callingPhoneNumber) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId btsId) = 0;
    virtual void sendSms(common::PhoneNumber nr, std::string text) = 0;
    virtual void sendCallRequest(common::PhoneNumber receiver) = 0;
    virtual void sendCallDrop(common::PhoneNumber receiver) = 0;
    virtual void sendCallAccept(common::PhoneNumber callingPhoneNumber) = 0;
};

}
