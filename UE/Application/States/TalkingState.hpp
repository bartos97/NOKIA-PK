#pragma once

#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

class TalkingState : public BaseState
{
public:
    TalkingState(Context& context);
};

}