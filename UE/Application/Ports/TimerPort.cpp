#include "TimerPort.hpp"
#include <thread>

namespace ue
{

TimerPort::TimerPort(common::ILogger& logger)
        : logger(logger, "[TIMER PORT]")
{}

void TimerPort::start(ITimerEventsHandler& handler)
{
    logger.logDebug("Started");
    this->handler = &handler;
}

void TimerPort::stop()
{
    logger.logDebug("Stoped");
    handler = nullptr;
}

void TimerPort::startTimer(Duration duration)
{
    logger.logDebug("Start timer: ", duration.count(), "ms");

    std::thread timerThread{[&, duration] {
        std::this_thread::sleep_for(duration);
        this->onTimerTimeout(std::this_thread::get_id());
    }};

    timers.emplace_back(timerThread.get_id());
    timerThread.detach();
}

void TimerPort::stopTimer()
{
    logger.logDebug("Stop timer");

    for (auto& timer : timers)
    {
        if (timer.isActive)
        {
            timer.isActive = false;
            return;
        }
    }
}

void TimerPort::onTimerTimeout(std::thread::id tid)
{
    for (auto& timer : timers)
    {
        if (timer.id == tid && timer.isActive)
        {
            handler->handleTimeout();
            return;
        }
    }
}
}
