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
    logger.logError("Unexpected: handleReceivingSms");
}

void BaseState::handleSendingSms(common::PhoneNumber nr, std::string text)
{
    logger.logError("Unexpected: handleSendingSms");
}

void BaseState::handleSendingCallRequest(common::PhoneNumber receiver)
{
    logger.logError("Unexpected: handleSendingCallRequest");
}

void BaseState::handleReceivingCallAccept(common::PhoneNumber converserNumber)
{
    logger.logError("Unexpected: handleReceivingCallAccept");
}

void BaseState::handleReceivingCallDropped(common::PhoneNumber converserNumber)
{
    logger.logError("Unexpected: handleReceivingCallDropped");
}

void BaseState::handleUnknownReceiver()
{
    logger.logError("Unexpected: handleUnknownReceiver");
}

void BaseState::handleSendingCallDrop(common::PhoneNumber receiver)
{
    logger.logError("Unexpected: handleSendingCallDrop");
}

}
