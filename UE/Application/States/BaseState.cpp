#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context& context, const std::string& name)
        : context(context),
          logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Unexpected: handleTimeout");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Unexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Unexpected: handleTimeout");
}

void BaseState::handleAttachReject()
{
    logger.logError("Unexpected: handleAttachReject");
}

void BaseState::handleDisconnected()
{
    logger.logError("Unexpected: handleDisconnected");
}

void BaseState::handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text)
{
    logger.logError("Unexpected: handleReceivingSms from ", senderNumber);
}

void BaseState::handleSendingSms(common::PhoneNumber nr, std::string text)
{
    logger.logError("Unexpected: handleSendingSms");
}

void BaseState::handleSendingCallRequest(common::PhoneNumber receiver)
{
    logger.logError("Unexpected: handleSendingCallRequest");
}

void BaseState::handleReceivingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleReceivingCallAccept");
}

void BaseState::handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleReceivingCallDrop");
}

void BaseState::handleUnknownReceiver()
{
    logger.logError("Unexpected: handleUnknownReceiver");
}

void BaseState::handleSendingCallDrop(common::PhoneNumber receiver)
{
    logger.logError("Unexpected: handleSendingCallDrop");
}

void BaseState::handleReceivingCallRequest(common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleReceivingCallRequest from ", callingPhoneNumber);
}

void BaseState::handleSendingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleSendingCallAccept to", callingPhoneNumber);
}
void BaseState::handleSendTalkMessage(const std::string message)
{
logger.logError("Unexpected handleSendTalkMessage", message);
}

void BaseState::handleTalkMessage(const std::string message)
{
logger.logError("Unexpected handle talk message", message);
}

}
