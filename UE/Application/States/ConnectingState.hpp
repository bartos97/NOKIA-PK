#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context, common::BtsId btsId);
    void handleAttachReject();
    void handleTimeout();
    void handleAttachAccept();
    void handleDisconnected();
};

}
