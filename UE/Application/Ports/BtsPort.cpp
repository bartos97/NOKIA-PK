#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{

}

void BtsPort::start(IBtsEventsHandler& handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) { handleMessage(msg); });
    transport.registerDisconnectedCallback([this] { handleDisconnected(); });
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId) {
            case common::MessageId::Sib: {
                auto btsId = reader.readBtsId();
                handler->handleSib(btsId);
                break;
            }
            case common::MessageId::AttachResponse: {
                bool accept = reader.readNumber<std::uint8_t>() != 0u;
                if (accept) {
                    handler->handleAttachAccept();
                } else
                    handler->handleAttachReject();
                break;
            }
            case common::MessageId::Sms: {
                bool number_exist = to == phoneNumber;
                if (number_exist) {
                    std::string text = reader.readRemainingText();
                    logger.logDebug("received sms text: ", text);
                    handler->handleReceivingSms(from, text);
                }
                break;
            }
        case common::MessageId::CallRequest: {
            bool number_exist = to == phoneNumber;
            if(number_exist)
            {
                handler->handleReceivingCall(from);
            }
            break;
        }
            default:
                logger.logError("unknown message: ", msgId, ", from: ", from);
        }
    }
    catch (std::exception const& ex) {
        logger.logError("handleMessage error: ", ex.what());
    }
}

void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::handleDisconnected()
{
    handler->handleDisconnected();
}

void BtsPort::sendingSms(common::PhoneNumber nr, std::string text)
{
    common::OutgoingMessage msg{common::MessageId::Sms, phoneNumber, nr};
    msg.writeText(text);
    transport.sendMessage(msg.getMessage());
    logger.logDebug("sent sms text: ", text);
}

void BtsPort::sendingCallAccept(common::PhoneNumber callingPhoneNumber)
{
     common::OutgoingMessage msg{common::MessageId::CallAccepted, phoneNumber, callingPhoneNumber};
     transport.sendMessage(msg.getMessage());
     logger.logDebug("sent accept call to: ", callingPhoneNumber);
}

void BtsPort::sendingCallDropped(common::PhoneNumber callingPhoneNumber)
{
     common::OutgoingMessage msg{common::MessageId::CallDropped, phoneNumber, callingPhoneNumber};
     transport.sendMessage(msg.getMessage());
     logger.logDebug("sent dropped call to: ", callingPhoneNumber);
}

}
