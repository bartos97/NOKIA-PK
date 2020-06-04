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
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
            case common::MessageId::Sib:
            {
                auto btsId = reader.readBtsId();
                handler->handleSib(btsId);
                break;
            }
            case common::MessageId::AttachResponse:
            {
                bool accept = reader.readNumber<std::uint8_t>() != 0u;
                if (accept)
                {
                    handler->handleAttachAccept();
                }
                else
                    handler->handleAttachReject();
                break;
            }
            case common::MessageId::Sms:
            {
                bool number_exist = to == phoneNumber;
                if (number_exist)
                {
                    std::string text = reader.readRemainingText();
                    logger.logDebug("received sms text: ", text);
                    handler->handleReceivingSms(from, text);
                }
                break;
            }
            case common::MessageId::CallRequest:
            {
                bool number_exist = to == phoneNumber;
                if (number_exist && to != from)
                {
                    handler->handleReceivingCallRequest(from);
                }
                break;
            }
            case common::MessageId::CallAccepted:
            {
                handler->handleReceivingCallAccept(from);
                break;
            }
            case common::MessageId::CallDropped:
            {
                handler->handleReceivingCallDrop(from);
                break;
            }
            case common::MessageId::UnknownRecipient:
            {
                auto unknownMsgId = reader.readMessageId();
                auto unknownFrom = reader.readPhoneNumber();
                auto unknownTo = reader.readPhoneNumber();
                switch (unknownMsgId)
                {
                    case common::MessageId::CallRequest:
                    {
                        handler->handleUnknownReceiver(unknownTo);
                        break;
                    }
                    case common::MessageId::CallDropped:
                    {
                        logger.logDebug("Received MessageId::UnknownRecipient after MessageId::CallDropped");

                        break;
                    }
                    case common::MessageId::CallAccepted:
                    {

                        logger.logDebug("Received MessageId::UnknownRecipient after MessageId::CallAccepted");
                        handler->handleUnknownReceiver(unknownTo);
                        break;
                    }
                    case common::MessageId::CallTalk:
                    {

                        logger.logDebug("Received MessageId::UnknownRecipient after MessageId::CallTalk");
                        break;
                    }
                    default:
                        logger.logError("Received MessageId::UnknownRecipient after unknown MessageId = ", unknownMsgId,
                                        ", from: ", unknownFrom);
                }

                break;
            }
            default:logger.logError("unknown message: ", msgId, ", from: ", from);
        }
    }
    catch (std::exception const& ex)
    {
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

void BtsPort::sendSms(common::PhoneNumber nr, std::string text)
{
    common::OutgoingMessage msg{common::MessageId::Sms, phoneNumber, nr};
    msg.writeText(text);
    transport.sendMessage(msg.getMessage());
    logger.logDebug("sent sms text: ", text);
}

void BtsPort::sendCallRequest(common::PhoneNumber receiver)
{
    common::OutgoingMessage msg{common::MessageId::CallRequest, phoneNumber, receiver};
    transport.sendMessage(msg.getMessage());
    logger.logDebug("sent call request to: ", receiver);
}

void BtsPort::sendCallDrop(common::PhoneNumber receiver)
{
    common::OutgoingMessage msg{common::MessageId::CallDropped, phoneNumber, receiver};
    transport.sendMessage(msg.getMessage());
    logger.logDebug("sent call drop to: ", receiver);
}

void BtsPort::sendCallAccept(common::PhoneNumber callingPhoneNumber)
{
    common::OutgoingMessage msg{common::MessageId::CallAccepted, phoneNumber, callingPhoneNumber};
    transport.sendMessage(msg.getMessage());
    logger.logDebug("sent accept call to: ", callingPhoneNumber);
}

//void BtsPort::sendUnknownRecipient(common::PhoneNumber callingPhoneNumber)
//{
//    common::OutgoingMessage msg{common::MessageId::UnknownRecipient, phoneNumber, callingPhoneNumber};
//    transport.sendMessage(msg.getMessage());
//    logger.logDebug("sent unknown recipient to: ", callingPhoneNumber);
//}

}
