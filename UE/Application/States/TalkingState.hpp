#pragma once

#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

class TalkingState : public BaseState
{
public:
    explicit TalkingState(Context& context);

    void handleUnknownReceiver(common::PhoneNumber callingPhoneNumber) override;

};


}
