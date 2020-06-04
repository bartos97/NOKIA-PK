#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include <deque>
#include <thread>

namespace ue
{

class TimerPort : public ITimerPort
{
private:
    struct Timer
    {
        std::thread::id id;
        bool isActive = true;
        Timer(std::thread::id tid) : id(tid)
        {}
    };

public:
    TimerPort(common::ILogger& logger);

    void start(ITimerEventsHandler& handler);
    void stop();

    // ITimerPort interface
    void startTimer(Duration duration) override;
    void stopTimer() override;

private:
    void onTimerTimeout(std::thread::id tid);

private:
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
    std::deque<Timer> timers;
};

}
