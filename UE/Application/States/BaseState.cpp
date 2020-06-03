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

void BaseState::handleReceivingSms(const common::PhoneNumber senderNumber, const std::string& text)
{
    logger.logError("Unexpected: handleReceivingSms from ", senderNumber);
}

void BaseState::handleSendingSms(common::PhoneNumber nr, std::string text)
{
    logger.logError("Unexpected: handleSendingSms");
}

void BaseState::handleReceivingCall(const common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleReceivingCall from ", callingPhoneNumber);
}

void BaseState::handleSendingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleSendingCallAccept to", callingPhoneNumber);
}

void BaseState::handleSendingCallDropped(common::PhoneNumber callingPhoneNumber)
{
    logger.logError("Unexpected: handleSendingCallDropped to", callingPhoneNumber);
}

}
