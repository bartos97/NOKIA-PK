#include "UserPort.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include <vector>
#include <iostream>
#include <string>

namespace ue
{
const std::function<void()> UserPort::EMPTY_CALLBACK = []{};

UserPort::UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler& handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
    gui.setAcceptCallback([this]{ onAccept(); });
    gui.setRejectCallback([this]{ onReject(); });
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    showMainMenuView();
}

void UserPort::showNewSms()
{
    gui.showNewSms();
}

void UserPort::addReceivedSms(const common::PhoneNumber senderNumber, const std::string& text)
{
    receivedSmsDb.emplace_back(senderNumber, phoneNumber, text);
}

void inline UserPort::setCurrentView(GUIView newView)
{
    previousView = currentView;
    currentView = newView;
    onReject = UserPort::EMPTY_CALLBACK;
    onAccept = UserPort::EMPTY_CALLBACK;
}

void UserPort::goToPreviousView()
{
    switch (previousView) {
        case GUIView::MAIN_MENU:
            showMainMenuView();
            return;
        case GUIView::SENT_SMS_LIST:
            showSentSmsListView();
            return;
        case GUIView::RECEIVED_SMS_LIST:
            showReceivedSmsListView();
            return;
        case GUIView::COMPOSE_SMS:
            showComposeSmsView();
            return;
        case GUIView::SMS:
            showMainMenuView();
            return;
    }
}

void UserPort::showMainMenuView()
{
    setCurrentView(GUIView::MAIN_MENU);

    auto& currentListView = gui.setListViewMode();
    currentListView.clearSelectionList();
    currentListView.addSelectionListItem("Compose SMS", "");
    currentListView.addSelectionListItem("View received SMSes", "");
    currentListView.addSelectionListItem("View sent SMSes", "");

    onAccept = [&]{
        switch (currentListView.getCurrentItemIndex().second) {
            case 0:
                showComposeSmsView();
                break;
            case 1:
                showReceivedSmsListView();
                break;
            case 2:
                showSentSmsListView();
                break;
        }
    };
}

void UserPort::showComposeSmsView()
{
    setCurrentView(GUIView::COMPOSE_SMS);
    auto& composeSms = gui.setSmsComposeMode();
    composeSms.clearSmsText();

    onAccept = [&]{
        SMS newSms{phoneNumber, composeSms.getPhoneNumber(), composeSms.getSmsText(), true};
        handler->handleSendingSms(newSms.receiverNumber, newSms.text);
        sentSmsDb.push_back(newSms);
        composeSms.clearSmsText();
        showMainMenuView();
    };

    onReject = [&]{
        showMainMenuView();
    };
}

void UserPort::showReceivedSmsListView()
{
    setCurrentView(GUIView::RECEIVED_SMS_LIST);
    showSmsList(receivedSmsDb);
}

void UserPort::showSentSmsListView()
{
    setCurrentView(GUIView::SENT_SMS_LIST);
    showSmsList(sentSmsDb);
}

void UserPort::showSmsList(const std::vector<SMS>& db)
{
    auto& currentListView = gui.setListViewMode();
    currentListView.clearSelectionList();

    std::string itemLabel, itemTooltip;
    for (const auto& sms : db) {
        itemLabel = sms.isRead ? "" : "[NEW] ";
        itemLabel += "From: " + common::to_string(sms.senderNumber);
        itemTooltip = sms.text.length() > MAX_TOOLTIP_LENGTH ?
                      sms.text.substr(0, MAX_TOOLTIP_LENGTH) + "..." : sms.text;
        currentListView.addSelectionListItem(itemLabel, itemTooltip);
    }

    onAccept = [&]{
        showSmsView(currentListView.getCurrentItemIndex().second);
    };

    onReject = [&]{
        goToPreviousView();
    };
}

void UserPort::showSmsView(size_t smsIndex)
{
    setCurrentView(GUIView::SMS);

    auto& sms = receivedSmsDb.at(smsIndex);
    IUeGui::ITextMode& smsView = gui.setViewTextMode();
    sms.isRead = true;
    smsView.setText(sms.text);

    onReject = [&]{
        goToPreviousView();
    };
}

}
