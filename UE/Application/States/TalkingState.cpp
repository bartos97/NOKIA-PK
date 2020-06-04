#include "TalkingState.hpp"

namespace ue
{

TalkingState::TalkingState(ue::Context& context)
        : BaseState(context, "TalkingState")
{

}

void TalkingState::handleUnknownReceiver(common::PhoneNumber callingPhoneNumber)
{
    logger.logInfo("Unknown receiver after call accepted");
    context.timer.stopTimer();
    context.user.showUnknownReceiver(callingPhoneNumber);
}


}
