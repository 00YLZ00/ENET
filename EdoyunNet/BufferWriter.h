#pragma once
#include <memory>
#include <queue>

class BufferWriter
{
private:
    /* data */
    typedef struct
    {
        std::shared_ptr<char> data;
        uint32_t size;
        uint32_t writeIndex;
    } Packet;

    std::queue<Packet> buffer_;
    int max_queue_length_ = 0;
    static const int kMaxQueueLength = 10000;

public:
    BufferWriter(int capacity = kMaxQueueLength);
    ~BufferWriter() {}

    bool Append(std::shared_ptr<char> data, uint32_t size, uint32_t index = 0);
    bool Append(const char *data, uint32_t size, uint32_t index = 0);
    int Send(int sockfd);

    bool IsEmpty() const
    {
        return buffer_.empty();
    }

    bool IsFull() const
    {
        return ((int)buffer_.size() >= max_queue_length_ ? true : false);
    }

    uint32_t Size() const
    {
        return (uint32_t)buffer_.size();
    }
};
