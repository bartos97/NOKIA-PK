#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class UserPort : public IUserPort
{
    struct Sms;
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();
    std::vector<Sms> getSmses();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void addSms(int from, const std::string &text) override;
    void showNewSms() override;
    void showComposeSms();


private:

    struct Sms{
        int number;
        const std::string text;
        Sms(int number,const std::string& text): number(number), text(text){}
    };
    void chooseMenu(IUeGui::IListViewMode& menu);
    std::vector<Sms> smses;
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
};

}
