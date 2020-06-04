#pragma once

#include <Messages/PhoneNumber.hpp>
#include "BaseState.hpp"

namespace ue
{

class TalkingState : public BaseState
{
public:
    TalkingState(Context& context, common::PhoneNumber from);
    void handleSendTalkMessage(std::string) final;
    void handleTalkMessage(std::string) final;
    void handleUnknownReceiver(common::PhoneNumber callingPhoneNumber) override;
    void handleSendingCallDrop(common::PhoneNumber receiver) override;
    void handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber) override;

private:
    common::PhoneNumber phone;
};

}
