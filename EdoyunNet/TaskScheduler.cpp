#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(int id) : id_(id), is_shutdown_(false)
{
}

TaskScheduler::~TaskScheduler()
{
}

void TaskScheduler::Start()
{
    is_shutdown_ = false;
}

void TaskScheduler::Stop()
{
    is_shutdown_ = true;
}

TimerId TaskScheduler::AddTimer(const TimerEvent &event, uint32_t mesc)
{
    return timer_queue_.AddTimer(event, mesc);
}

void TaskScheduler::RemoveTimer(TimerId timerId)
{
    timer_queue_.RemoveTimer(timerId);
}
