#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BtsPort : public IBtsPort
{
public:
    BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
    void start(IBtsEventsHandler& handler);
    void stop();

    void sendAttachRequest(common::BtsId btsId) override;
    void sendSms(common::PhoneNumber nr, std::string text) override;

    void sendCallRequest(common::PhoneNumber receiver) override;
    void sendCallDrop(common::PhoneNumber receiver) override;
    void sendingCallAccept(common::PhoneNumber callingPhoneNumber) override;

private:
    void handleMessage(BinaryMessage msg);
    void handleDisconnected();

    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;

    IBtsEventsHandler* handler = nullptr;
};

}
