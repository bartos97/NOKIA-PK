#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "TalkingState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context& context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    logger.logInfo("Disconnected");
    context.setState<NotConnectedState>();
}

void ConnectedState::handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text)
{
    logger.logInfo("Receive sms from: ", senderNumber);
    context.user.addReceivedSms(senderNumber, text);
    context.user.showNewSms();
}

void ConnectedState::handleSendingSms(common::PhoneNumber nr, std::string text)
{
    logger.logInfo("Send sms to ", nr);
    context.bts.sendingSms(nr, text);
}

void ConnectedState::handleReceivingCall(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Receiviving call from: ", callingPhoneNumber);
    using namespace std::chrono_literals;
    context.timer.startTimer(30000ms);
    context.user.showCallRequest(callingPhoneNumber);
}

void ConnectedState::handleSendingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Call accepted from: ", callingPhoneNumber);
    context.timer.stopTimer();
    context.bts.sendingCallAccept(callingPhoneNumber);
    context.setState<TalkingState>();
}

void ConnectedState::handleSendingCallDropped(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Call dropped from: ", callingPhoneNumber);
    context.timer.stopTimer();
    context.bts.sendingCallDropped(callingPhoneNumber);
    context.user.showConnected();
}




}
