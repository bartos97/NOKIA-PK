#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include <vector>
#include <iostream>
#include <string>

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
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

void UserPort::showComposeSms(){
    IUeGui::ISmsComposeMode& composeSms = gui.setSmsComposeMode();
    gui.setAcceptCallback([&](){handler->handleSendingSms(composeSms.getPhoneNumber(),composeSms.getSmsText());
            composeSms.clearSmsText();
            showConnected();
        });
        gui.setRejectCallback([&](){
            showConnected();
        });
    }

    void UserPort:: chooseMenu(IUeGui::IListViewMode& menu){
        gui.setAcceptCallback([&](){
            switch(menu.getCurrentItemIndex().second){
                case 0:
                    showComposeSms();
                    break;

            }
        });
    }


void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    chooseMenu(menu);
}

void UserPort::addSms(int from, const std::string &text)
{
    Sms sms{from, text};
    smses.push_back(sms);
}

void UserPort::showNewSms()
{
    gui.showNewSms();
}

std::vector<UserPort::Sms> UserPort::getSmses()
{
    return smses;
}

}
