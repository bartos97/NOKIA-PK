#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{  context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    logger.logInfo("Disconnected");
    context.setState<NotConnectedState>();
}

void ConnectedState::handleReceivingSms(int from, const std::string &text)
{
    logger.logInfo("Receive sms from ", from);
    context.user.addSms(from, text);
    //context.user.showNewSms();
}

void ConnectedState::handleSendingSms(common::PhoneNumber nr, std::string text)
{
    logger.logInfo("Send sms to ", nr);
    context.bts.sendingSms(nr, text);

}

}
