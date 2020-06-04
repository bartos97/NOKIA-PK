#include "TalkingState.hpp"

namespace ue
{

TalkingState::TalkingState(Context& context, const common::PhoneNumber from)
        : BaseState(context, "TalkingState"), phone{from}
{
    context.user.showCallView("");
}

void TalkingState::handleSendTalkMessage(const std::string message)
{
    context.timer.stopTimer();
    using namespace std::chrono_literals;
    context.timer.startTimer(120000ms);
    context.bts.sendTalkMessage(message, phone);
}

void TalkingState::handleTalkMessage(const std::string message)
{
    context.timer.stopTimer();
    using namespace std::chrono_literals;
    context.timer.startTimer(120000ms);
    context.user.showCallView(message);
}

void TalkingState::handleUnknownReceiver(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Unknown receiver after call accepted");
    context.timer.stopTimer();
    context.user.showUnknownReceiver(callingPhoneNumber);
}

void TalkingState::handleSendingCallDrop(common::PhoneNumber receiver)
{
    logger.logInfo("Sending call drop to: ", receiver);
    context.timer.stopTimer();
    context.bts.sendCallDrop(receiver);
    context.user.showConnected();
}

void TalkingState::handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Received call drop");
    context.timer.stopTimer();
    context.user.showCallingDropped(callingPhoneNumber);
}
}
