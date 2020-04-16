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

}
