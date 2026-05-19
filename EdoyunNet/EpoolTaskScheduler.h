#include "TaskScheduler.h"
#include <unordered_map>

class EpoolTaskScheduler : public TaskScheduler
{
private:
    /* data */
    int epollfd_ = -1;
    std::mutex mutex_;
    std::unordered_map<int, ChannelPtr> channels_;

public:
    EpoolTaskScheduler(int id=0);
    virtual ~EpoolTaskScheduler();
    virtual void UpdateChannel(ChannelPtr channel);
    virtual void RemoveChannel(ChannelPtr channel);
    virtual bool HandleEvent();

protected:
    void Update(int operation, ChannelPtr &Channel);
};
