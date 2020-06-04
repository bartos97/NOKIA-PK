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
    context.bts.sendSms(nr, text);
}

void ConnectedState::handleSendingCallRequest(common::PhoneNumber receiver)
{
    logger.logInfo("Send call request to ", receiver);
    context.bts.sendCallRequest(receiver);
    context.timer.startTimer(std::chrono::seconds{60});
}

void ConnectedState::handleReceivingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Received call accept");
    context.timer.stopTimer();
    context.user.showCallingConnected(callingPhoneNumber);
    context.setState<TalkingState>();
}

void ConnectedState::handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Received call drop");
    context.timer.stopTimer();
    context.user.showCallingDropped(callingPhoneNumber);
}

void ConnectedState::handleUnknownReceiver()
{
    logger.logInfo("Unknown receiver");
    context.timer.stopTimer();
    context.user.showUnknownReceiver();
}

void ConnectedState::handleTimeout()
{
    logger.logInfo("Timeout");
    context.user.showCallingTimeout();
}

void ConnectedState::handleSendingCallDrop(common::PhoneNumber receiver)
{
    logger.logInfo("Sending call drop to: ", receiver);
    context.timer.stopTimer();
    context.bts.sendCallDrop(receiver);
    context.user.showConnected();
}

void ConnectedState::handleReceivingCallRequest(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Receiving call from: ", callingPhoneNumber);
    using namespace std::chrono_literals;
    context.timer.startTimer(30000ms);
    context.user.showCallRequest(callingPhoneNumber);
}

void ConnectedState::handleSendingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Sending call accept to: ", callingPhoneNumber);
    context.timer.stopTimer();
    context.bts.sendCallAccept(callingPhoneNumber);
    context.user.showCallingConnected(callingPhoneNumber);
    context.setState<TalkingState>();
}

}
