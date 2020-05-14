#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

enum class GUIView
{
    MAIN_MENU,
    COMPOSE_SMS,
    RECEIVED_SMS_LIST,
    SENT_SMS_LIST,
    SMS
};

enum class MainMenuItem
{
    COMPOSE_SMS,
};

class UserPort : public IUserPort
{
public:
    struct SMS
    {
        const common::PhoneNumber senderNumber;
        const std::string text;
        bool isRead;

        SMS(const common::PhoneNumber senderNumber, const std::string& text)
                : senderNumber(senderNumber), text(text), isRead(false)
        {}
    };

public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();
    const std::vector<SMS>& getSMSes();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void addReceivedSms(const common::PhoneNumber senderNumber, const std::string& text) override;
    void showNewSms() override;

private:
    void changeCurrentView(GUIView newView);
    void goToView(GUIView view);
    void showMainMenu();
    void mainMenuAcceptCallback(IUeGui::IListViewMode& menu);
    void showComposeSmsView();
    void showReceivedSmsListView();
    void showSentSmsListView();
    void showSmsView(size_t smsIndex);

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler *handler = nullptr;

    std::vector<SMS> SMSes;
    GUIView currentView;
    GUIView previousView;
};

}
