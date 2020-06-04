#include "UserPort.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include <vector>
#include <string>

namespace ue
{
const std::function<void()> UserPort::EMPTY_CALLBACK = [] {};

UserPort::UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber)
        : logger(logger, "[USER-PORT]"),
          gui(gui),
          phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler& handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
    gui.setAcceptCallback([this] { onAccept(); });
    gui.setRejectCallback([this] { onReject(); });
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    setCurrentView(GUIView::NOT_CONNECTED);
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    setCurrentView(GUIView::CONNECTING);
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
    switch (previousView)
    {
        case GUIView::MAIN_MENU:showMainMenuView();
            return;
        case GUIView::SENT_SMS_LIST:showSentSmsListView();
            return;
        case GUIView::RECEIVED_SMS_LIST:showReceivedSmsListView();
            return;
        case GUIView::COMPOSE_SMS:showComposeSmsView();
            return;
        case GUIView::SMS:showMainMenuView();
            return;
        case GUIView::DIAL:showDialView();
            return;
        case GUIView::INVALID:
        case GUIView::NOT_CONNECTED:
        case GUIView::CONNECTING:
        case GUIView::CALLING:
        default:
            showMainMenuView();
    }
}

void UserPort::showMainMenuView()
{
    setCurrentView(GUIView::MAIN_MENU);

    auto& currentListView = gui.setListViewMode();
    currentListView.clearSelectionList();
    currentListView.addSelectionListItem("Dial", "");
    currentListView.addSelectionListItem("Compose SMS", "");
    currentListView.addSelectionListItem("View received SMSes", "");
    currentListView.addSelectionListItem("View sent SMSes", "");

    onAccept = [&] {
        switch (currentListView.getCurrentItemIndex().second)
        {
            case 0:showDialView();
                break;
            case 1:showComposeSmsView();
                break;
            case 2:showReceivedSmsListView();
                break;
            case 3:showSentSmsListView();
                break;
            default:showDialView();
                break;
        }
    };
}

void UserPort::showComposeSmsView()
{
    setCurrentView(GUIView::COMPOSE_SMS);
    auto& composeSms = gui.setSmsComposeMode();
    composeSms.clearSmsText();

    onAccept = [&] {
        SMS newSms{phoneNumber, composeSms.getPhoneNumber(), composeSms.getSmsText(), true};
        handler->handleSendingSms(newSms.receiverNumber, newSms.text);
        sentSmsDb.push_back(newSms);
        composeSms.clearSmsText();
        showMainMenuView();
    };

    onReject = [&] {
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
    for (const auto& sms : db)
    {
        itemLabel = sms.isRead ? "" : "[NEW] ";
        itemLabel += "From: " + common::to_string(sms.senderNumber);
        itemTooltip = sms.text.length() > MAX_TOOLTIP_LENGTH ?
                      sms.text.substr(0, MAX_TOOLTIP_LENGTH) + "..." : sms.text;
        currentListView.addSelectionListItem(itemLabel, itemTooltip);
    }

    onAccept = [&] {
        showSmsView(currentListView.getCurrentItemIndex().second);
    };

    onReject = [&] {
        goToPreviousView();
    };
}

void UserPort::showSmsView(size_t smsIndex)
{
    setCurrentView(GUIView::SMS);

    try
    {
        auto& sms = receivedSmsDb.at(smsIndex);
        IUeGui::ITextMode& smsView = gui.setViewTextMode();
        sms.isRead = true;
        smsView.setText(sms.text);
    }
    catch (const std::out_of_range& e)
    {
        logger.logDebug(e.what());
        goToPreviousView();
    }

    onReject = [&] {
        goToPreviousView();
    };
}

void UserPort::showDialView()
{
    setCurrentView(GUIView::DIAL);
    bool isDialing = false;
    auto& dialView = gui.setDialMode();

    onAccept = [&] {
        currentReceiver = dialView.getPhoneNumber();
        handler->handleSendingCallRequest(currentReceiver);
        isDialing = true;
    };

    onReject = [&] {
        if (isDialing)
            dropCurrentCall();
    };
}

void UserPort::showCallingConnected(const common::PhoneNumber callingPhoneNumber)
{
    setCurrentView(GUIView::CALLING);
    auto& callingView = gui.setCallMode();
    callingView.appendIncomingText("Talking with: " + to_string(callingPhoneNumber));

    //TODO: onAccept, onReject
}

void UserPort::showCallingDropped(const PhoneNumber callingPhoneNumber)
{
    setCurrentView(GUIView::CALLING);
    auto& callingView = gui.setCallMode();
    callingView.appendIncomingText("Phone " + to_string(callingPhoneNumber) + " dropped call.");
    currentReceiver.value = common::PhoneNumber::INVALID_VALUE;
    showMainMenuView();
}

void UserPort::showUnknownReceiver()
{
    setCurrentView(GUIView::CALLING);
    auto& callingView = gui.setCallMode();
    callingView.appendIncomingText("Receiver is not connected");
    currentReceiver.value = common::PhoneNumber::INVALID_VALUE;
    showMainMenuView();
}

void UserPort::showCallingTimeout()
{
    if (currentReceiver.value != common::PhoneNumber::INVALID_VALUE)
    {
        dropCurrentCall();
    }
}

void UserPort::dropCurrentCall()
{
    handler->handleSendingCallDrop(currentReceiver);
    currentReceiver.value = common::PhoneNumber::INVALID_VALUE;
}

void UserPort::showCallRequest(common::PhoneNumber callingPhoneNumber)
{
    setCurrentView(GUIView::CALLING);
    auto& callingView = gui.setCallMode();
    callingView.appendIncomingText("Incoming call from: " + to_string(callingPhoneNumber));
    currentReceiver = callingPhoneNumber;

    onAccept = [&, callingPhoneNumber] {
        handler->handleSendingCallAccept(callingPhoneNumber);
    };

    onReject = [&, callingPhoneNumber] {
        handler->handleSendingCallDrop(callingPhoneNumber);
    };
}

}
