#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger& iLogger,
                         IBtsPort& bts,
                         IUserPort& user,
                         ITimerPort& timer)
        : context{iLogger, bts, user, timer},
          logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}

void Application::handleDisconnected()
{
    context.state->handleDisconnected();
}

void Application::handleReceivingSms(common::PhoneNumber senderNumber, const std::string& text)
{
    context.state->handleReceivingSms(senderNumber, text);
}

void Application::handleSendingSms(common::PhoneNumber nr, std::string text)
{
    context.state->handleSendingSms(nr, text);
}

void Application::handleReceivingCallRequest(common::PhoneNumber callingPhoneNumber)
{
    context.state->handleReceivingCallRequest(callingPhoneNumber);
}

void Application::handleSendingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    context.state->handleSendingCallAccept(callingPhoneNumber);
}

void Application::handleSendingCallRequest(common::PhoneNumber receiver)
{
    context.state->handleSendingCallRequest(receiver);
}

void Application::handleReceivingCallAccept(common::PhoneNumber callingPhoneNumber)
{
    context.state->handleReceivingCallAccept(callingPhoneNumber);
}

void Application::handleReceivingCallDrop(common::PhoneNumber callingPhoneNumber)
{
    context.state->handleReceivingCallDrop(callingPhoneNumber);
}

void Application::handleUnknownReceiver()
{
    context.state->handleUnknownReceiver();
}

void Application::handleSendingCallDrop(common::PhoneNumber receiver)
{
    context.state->handleSendingCallDrop(receiver);
}

}
