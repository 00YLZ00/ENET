#include "BufferWriter.h"
#include <string.h>
#include <sys/socket.h>
#include <errno.h>

BufferWriter::BufferWriter(int capacity) : max_queue_length_(capacity)
{
}

bool BufferWriter::Append(std::shared_ptr<char> data, uint32_t size, uint32_t index)
{
    if (size < index)
    {
        return false;
    }
    if (buffer_.size() >= max_queue_length_)
    {
        return false;
    }
    Packet pkt = {data, size, index};
    buffer_.emplace(std::move(pkt));
    return true;
}

bool BufferWriter::Append(const char *data, uint32_t size, uint32_t index)
{
    if (size < index)
    {
        return false;
    }
    if (buffer_.size() >= max_queue_length_)
    {
        return false;
    }
    Packet pkt;
    pkt.data.reset(new char[size + 512], std::default_delete<char[]>());
    memcpy(pkt.data.get(), data, size);
    pkt.size = size;
    pkt.writeIndex = index;
    buffer_.emplace(std::move(pkt));
    return true;
}

int BufferWriter::Send(int sockfd)
{
    int ret = 0;
    int count = 1;
    do
    {
        if (buffer_.empty())
        {
            return 0;
        }
        count -= 1;
        Packet &pkt = buffer_.front();
        ret = ::send(sockfd, pkt.data.get() + pkt.writeIndex, pkt.size - pkt.writeIndex, 0);
        if (ret > 0)
        {
            pkt.writeIndex += ret;
            if (pkt.size == pkt.writeIndex)
            {
                count += 1;
                buffer_.pop();
            }
        }
        else if (ret < 0)
        {
            if (errno == EINTR || errno == EAGAIN)
            {
                ret = 0;
            }
        }
    } while (count > 0);
    return ret;
}
