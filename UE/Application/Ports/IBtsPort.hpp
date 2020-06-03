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
    virtual void handleReceivingCall(common::PhoneNumber callingPhoneNumber) = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendingSms(common::PhoneNumber, std::string) = 0;
    virtual void sendingCallAccept(common::PhoneNumber) = 0;
    virtual void sendingCallDropped(common::PhoneNumber) = 0;
};

}
