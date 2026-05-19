#include <cstdint>
#include "Timer.h"
#include "Channel.h"
#include<atomic>
#include<mutex>

class TaskScheduler
{
private:
    /* data */
    int id_=0;
    std::atomic_bool is_shutdown_;
    std::mutex mutex_;
    TimerQueue timer_queue_;
public:
    TaskScheduler(int id = 1);
    virtual ~TaskScheduler();
    void Start();
    void Stop();
    TimerId AddTimer(const TimerEvent &event, uint32_t mesc);
    void RemoveTimer(TimerId timerId);
    virtual void UpdateChannel(ChannelPtr channel) {};
    virtual void RemoveChannel(ChannelPtr channel) {};
    virtual bool HandleEvent()
    {
        return false;
    }
    inline int GetId() const
    {
        return id_;
    }
};