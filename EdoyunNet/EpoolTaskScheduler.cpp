#include "EpoolTaskScheduler.h"
#include <sys/epoll.h>
#include <iostream>

EpoolTaskScheduler::EpoolTaskScheduler(int id) : TaskScheduler(id)
{
    epollfd_ = epoll_create(1024);
}

EpoolTaskScheduler::~EpoolTaskScheduler()
{
}

void EpoolTaskScheduler::UpdateChannel(ChannelPtr channel)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int fd = channel->GetSocket();
    if (channels_.find(fd) != channels_.end())
    {
        if (channel->IsNoneEvent())
        {
            Update(EPOLL_CTL_DEL, channel);
            channels_.erase(fd);
        }
        else
        {
            Update(EPOLL_CTL_MOD, channel);
        }
    }
    else
    {
        if (!channel->IsNoneEvent())
        {
            channels_.emplace(fd, channel);
            Update(EPOLL_CTL_ADD, channel);
        }
    }
}

void EpoolTaskScheduler::RemoveChannel(ChannelPtr channel)
{
    std::lock_guard<std::mutex> lock(mutex_);
    int fd = channel->GetSocket();
    if (channels_.find(fd) != channels_.end())
    {
        Update(EPOLL_CTL_DEL, channel);
        channels_.erase(fd);
    }
}

bool EpoolTaskScheduler::HandleEvent()
{
    epoll_event events[512]={0};
    int num_events=-1;
    num_events=epoll_wait(epollfd_,events,512,0);
    if(num_events<0){
        if(errno!=EINTR){
            return false;
        }
    }
    for(int i=0;i<num_events;i++){
        if(events[i].data.ptr){
            ((Channel*)events[i].data.ptr)->HandleEvent(events[i].events);
        }
    }
    return false;
}

void EpoolTaskScheduler::Update(int operation, ChannelPtr &Channel)
{
    epoll_event event = {0};
    if (operation != EPOLL_CTL_DEL)
    {
        event.data.ptr = Channel.get();
        event.events = Channel->GetEvents();
    }
    if (::epoll_ctl(epollfd_, operation, Channel->GetSocket(), &event) < 0)
    {
        std::cout << "修改epoll事件失败\n";
    }
}
