#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "UeGui/IListViewMode.hpp"
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
        const common::PhoneNumber receiverNumber;
        const std::string text;
        bool isRead;

        SMS(const common::PhoneNumber senderNumber, const common::PhoneNumber receiverNumber)
            : senderNumber(senderNumber), receiverNumber(receiverNumber)
        {}

        SMS(const common::PhoneNumber senderNumber, const common::PhoneNumber receiverNumber, const std::string& text, bool isRead = false)
            : senderNumber(senderNumber), receiverNumber(receiverNumber), text(text), isRead(isRead)
        {}
    };

public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    const std::vector<UserPort::SMS>& getReceivedSMSes()
    { return receivedSmsDb; }

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showNewSms() override;
    void addReceivedSms(const common::PhoneNumber senderNumber, const std::string& text) override;

private:
    void setCurrentView(GUIView newView);
    void goToPreviousView();

    void showMainMenuView();
    void showComposeSmsView();
    void showReceivedSmsListView();
    void showSentSmsListView();
    void showSmsList(const std::vector<SMS>& db);
    void showSmsView(size_t smsIndex);

private:
    static const std::function<void()> EMPTY_CALLBACK;
    static constexpr unsigned int MAX_TOOLTIP_LENGTH = 30;

    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;

    GUIView currentView;
    GUIView previousView;
    std::function<void()> onAccept;
    std::function<void()> onReject;

    std::vector<SMS> receivedSmsDb;
    std::vector<SMS> sentSmsDb;
};

}
