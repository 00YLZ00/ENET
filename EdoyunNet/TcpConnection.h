#pragma once
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Channel.h"
#include "TcpSocket.h"
#include "TaskScheduler.h"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    using Ptr = std::shared_ptr<TcpConnection>;
    using DisConnectCallback = std::function<void(std::shared_ptr<TcpConnection>)>;
    using CloseCallback = std::function<void(std::shared_ptr<TcpConnection>)>;
    using ReadCallback = std::function<bool(std::shared_ptr<TcpConnection>, BufferReader &buffer)>;

private:
    std::shared_ptr<Channel> channel_ = nullptr;
    DisConnectCallback disconnectCb_;
    CloseCallback closeCb_;
    ReadCallback readCb_;

protected:
    friend class TcpServer;
    void SetDisConnectCallback(const DisConnectCallback &cb) { disconnectCb_ = cb; }
    bool is_closed_;
    TaskScheduler *task_schduler_;
    std::unique_ptr<BufferReader> read_buffer_;
    std::unique_ptr<BufferWriter> write_buffer_;

public:
    TcpConnection(TaskScheduler *task_schduler, int sockfd);
    virtual ~TcpConnection();
    inline TaskScheduler *GetTaskSchduler() const { return task_schduler_; }
    inline void SetReadCallback(const ReadCallback &cb) { readCb_ = cb; }
    inline void SetCloseCallback(const CloseCallback &cb) { closeCb_ = cb; }
    inline bool IsClose() const { return is_closed_; }
    inline int GetSocket() const { return channel_->GetSocket(); }
    void Send(std::shared_ptr<char> data, uint32_t size);
    void Send(const char *data, uint32_t size);
    void DisConnect();

protected:
    void Close();
    virtual void HandleRead();
    virtual void HandleWrite();
    virtual void HandleClose();
    virtual void HandleError();
};
