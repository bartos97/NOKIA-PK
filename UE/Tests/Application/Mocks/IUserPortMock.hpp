#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

    MOCK_METHOD(void, handleSendingSms, (common::PhoneNumber receiver, std::string content), (final));
    MOCK_METHOD(void, handleSendingCallRequest, (common::PhoneNumber receiver), (final));
    MOCK_METHOD(void, handleSendingCallAccept, (common::PhoneNumber callingPhoneNumber ), (final));
    MOCK_METHOD(void, handleSendingCallDrop, (common::PhoneNumber callingPhoneNumber ), (final));
    MOCK_METHOD(void, handleSendTalkMessage, (std::string string), (final));
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, addReceivedSms, (const common::PhoneNumber senderNumber, const std::string& text), (final));
    MOCK_METHOD(void, showNewSms, (), (final));
    MOCK_METHOD(void, showCallRequest, (common::PhoneNumber callingPhoneNumber), (final));
    MOCK_METHOD(void, showCallingConnected, (common::PhoneNumber callingPhoneNumber), (final));
    MOCK_METHOD(void, showCallingDropped, (common::PhoneNumber callingPhoneNumber), (final));
    MOCK_METHOD(void, showCallingTimeout, (), (final));
    MOCK_METHOD(void, showUnknownReceiver, (common::PhoneNumber callingPhoneNumber), (final));
    MOCK_METHOD(void, showCallView, (std::string string), (final));
};

}
