#pragma once
#include <string>
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;

    virtual void addReceivedSms(const common::PhoneNumber senderNumber, const std::string &text) = 0;
    virtual void showNewSms() = 0;
};

}
