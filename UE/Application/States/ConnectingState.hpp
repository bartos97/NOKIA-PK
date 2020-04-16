#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context);
    void handleAttachReject() override;
    void handleTimeout() override;
    void handleAttachAccept() override;
    void handleDisconnected() override;
};

}
