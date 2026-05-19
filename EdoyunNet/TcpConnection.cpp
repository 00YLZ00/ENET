#include "TcpConnection.h"
#include <unistd.h>

TcpConnection::TcpConnection(TaskScheduler *task_schduler, int sockfd)
    : task_schduler_(task_schduler), read_buffer_(new BufferReader()), write_buffer_(new BufferWriter(500)), channel_(new Channel(sockfd))
{
    is_closed_ = false;

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
    if(readCb_){
        // bool ret=readCb_(shared_from_this(),*read_buffer_);
        if(!ret)
        {
            this->Close();
        }
    }
}

void TcpConnection::HandleWrite()
{
}

void TcpConnection::HandleClose()
{
}

void TcpConnection::HandleError()
{
}
