#pragma once
#include "TcpConnection.h"
#include <unistd.h>
#include<cstring>

TcpConnection::TcpConnection(TaskScheduler *task_schduler, int sockfd)
    : task_schduler_(task_schduler), read_buffer_(new BufferReader()), write_buffer_(new BufferWriter(500)), channel_(new Channel(sockfd))
{
    is_closed_ = false;
    //
    task_schduler_->AddTimer([this]()
                             {
        char buffer[] = "hello,I am server1"; 
        //std::string buffer= "你好，我是服务器"; 
        
        this->Send(buffer,strlen(buffer));
        //this->Send(buffer.data(),buffer.size());
        return true; }, 1000);
    task_schduler_->AddTimer([this]()
                             {
        char buffer[] = "hello,I am server2"; 
        //std::string buffer= "你好，我是服务器"; 
        
        this->Send(buffer,strlen(buffer));
        //this->Send(buffer.data(),buffer.size());
        return true; }, 500);

    //

    channel_->SetReadCallback([this]()
                              { this->HandleRead(); });
    channel_->SetWriteCallback([this]()
                               { this->HandleWrite(); });
    channel_->SetCloseCallback([this]()
                               { this->HandleClose(); });
    channel_->SetErrorCallback([this]()
                               { this->HandleError(); });

    // 设置套接字属性
    SocketUtil::SetNonBlock(sockfd);
    SocketUtil::SetSendBufSize(sockfd, 100 * 1024);
    SocketUtil::SetKeepAlive(sockfd);

    channel_->EnableReading();
    task_schduler->UpdateChannel(channel_);
}

TcpConnection::~TcpConnection()
{
    int fd = channel_->GetSocket();
    if (fd > 0)
    {
        ::close(fd);
    }
}

void TcpConnection::Send(std::shared_ptr<char> data, uint32_t size)
{
    if (!is_closed_)
    {
        write_buffer_->Append(data, size);
        this->HandleWrite();
    }
}

void TcpConnection::Send(const char *data, uint32_t size)
{
    if (!is_closed_)
    {
        write_buffer_->Append(data, size);
        this->HandleWrite();
    }
}

void TcpConnection::DisConnect()
{
    this->Close();
}

void TcpConnection::Close()
{
    if (!is_closed_)
    {
        is_closed_ = true;
        task_schduler_->RemoveChannel(channel_);
        if (is_closed_)
        {
            closeCb_(shared_from_this());
        }
        if (disconnectCb_)
        {
            disconnectCb_(shared_from_this());
        }
    }
}

void TcpConnection::HandleRead()
{
    if (is_closed_)
    {
        return;
    }
    int ret = read_buffer_->Read(channel_->GetSocket());
    if (ret < 0)
    {
        this->Close();
        return;
    }
    if (readCb_)
    {
        bool ret = readCb_(shared_from_this(), *read_buffer_);
        if (!ret)
        {
            this->Close();
        }
    }
    //
    std::string data;
    uint32_t size =read_buffer_->ReadAll(data);
    if(size)
    {
        this->Send(data.data(),data.size());
    }
}

void TcpConnection::HandleWrite()
{
    if (is_closed_)
    {
        return;
    }
    int ret = 0;
    bool empty = false;
    do
    {
        ret = write_buffer_->Send(channel_->GetSocket());
        if (ret < 0)
        {
            this->Close();
            return;
        }
        empty = write_buffer_->IsEmpty();
    } while (0);
    if (empty)
    {
        if (channel_->IsWriting())
        {
            channel_->DisableWriting();
            task_schduler_->UpdateChannel(channel_);
        }
    }
    else if (!channel_->IsWriting())
    {
        channel_->EnableWriting();
        task_schduler_->UpdateChannel(channel_);
    }
}

void TcpConnection::HandleClose()
{
    this->Close();
}

void TcpConnection::HandleError()
{
    this->Close();
}
