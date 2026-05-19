#include "EpoolTaskScheduler.h"
#include<sys/epoll.h>

EpoolTaskScheduler::EpoolTaskScheduler(int id):TaskScheduler(id)
{
    epollfd_=epoll_create(1024);
}

EpoolTaskScheduler::~EpoolTaskScheduler()
{
}

void EpoolTaskScheduler::UpdateChannel(ChannelPtr channel)
{
}

void EpoolTaskScheduler::RemoveChannel(ChannelPtr channel)
{
}

bool EpoolTaskScheduler::HandleEvent()
{
    return false;
}

void EpoolTaskScheduler::Update(int operation, ChannelPtr &Channel)
{
}
