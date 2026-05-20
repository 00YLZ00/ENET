#pragma once
#include "EpoolTaskScheduler.h"
#include <vector>

class EventLoop
{
private:
    /* data */
    uint32_t num_threads_ = 1;
    uint32_t index_ = 1;
    std::vector<std::shared_ptr<TaskScheduler>> task_schdulers_;
    std::vector<std::shared_ptr<std::thread>> threads_;

public:
    EventLoop(const EventLoop &) = delete;
    EventLoop &operator=(const EventLoop &) = delete;

    EventLoop(uint32_t num_threads=-1);
    ~EventLoop();
    std::shared_ptr<TaskScheduler>GetTaskSchduler();
    TimerId AddTimer(const TimerEvent& event,uint32_t mesc);
    void RemoveTimer(TimerId TimerId);
    void UpdateChannel(ChannelPtr channel);
    void RemoveChannel(ChannelPtr& channel);
    void Loop();
    void Quit();
};