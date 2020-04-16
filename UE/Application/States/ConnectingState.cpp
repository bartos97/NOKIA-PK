#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"
#include "ConnectedState.hpp"

namespace ue
{

ConnectingState::ConnectingState(Context &context, common::BtsId btsId)
    : BaseState(context, "ConnectingState")
{
    using namespace std::literals;

    context.user.showConnecting();
    context.bts.sendAttachRequest(btsId);
    context.timer.startTimer(500ms);
}

void ConnectingState::handleTimeout()
{
    context.logger.logError("Connection timed out");
    context.setState<NotConnectedState>();
}

void ConnectingState::handleAttachAccept()
{
    context.logger.logInfo("Attach accept");
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void ConnectingState::handleAttachReject(){
    context.logger.logError("Attach rejected");
    context.timer.stopTimer();
    context.setState<NotConnectedState>();
}

void ConnectingState::handleDisconnected()
{
    logger.logInfo("Disconnected");
    context.setState<NotConnectedState>();
}

}
