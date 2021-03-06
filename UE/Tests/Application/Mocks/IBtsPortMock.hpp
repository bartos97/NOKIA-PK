#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleReceivingSms, (const common::PhoneNumber senderNumber, const std::string& text), (final));
    MOCK_METHOD(void, handleReceivingCallRequest, (const common::PhoneNumber senderNumber), (final));
    MOCK_METHOD(void, handleReceivingCallDrop, (const common::PhoneNumber senderNumber), (final));
    MOCK_METHOD(void, handleReceivingCallAccept, (const common::PhoneNumber senderNumber), (final));
    MOCK_METHOD(void, handleUnknownReceiver, (common::PhoneNumber callingPhoneNumber), (final));
    MOCK_METHOD(void, handleTalkMessage, (std::string string), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber receiver), (final));
    MOCK_METHOD(void, sendCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallDrop, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendTalkMessage, (std::string string, common::PhoneNumber number), (final));
};

}
