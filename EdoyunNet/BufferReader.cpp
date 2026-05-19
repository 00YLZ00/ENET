#include "BufferReader.h"
#include <unistd.h>
#include <sys/socket.h>

BufferReader::BufferReader(uint32_t initial_size)
{
}

BufferReader::~BufferReader()
{
}

int BufferReader::Read(int fd)
{
    uint32_t size = WritableBytes();
    if (size < MAX_BYTES_PER_READ)
    {
        uint32_t bufferReadSize = buffer_.size();
        if (bufferReadSize > MAX_BUFFER_SIZE)
        {
            return 0;
        }
        buffer_.resize(bufferReadSize + MAX_BYTES_PER_READ);
    }
    int bytes_read = ::recv(fd, BeginWrite(), MAX_BYTES_PER_READ, 0);
    if (bytes_read > 0)
    {
        writer_index_ += bytes_read;
    }
    return bytes_read;
}

uint32_t BufferReader::ReadAll(std::string &data)
{
    uint32_t size = ReadableBytes();
    if (size > 0)
    {
        data.assign(Peek(), size);
        writer_index_ = 0;
        reader_index_ = 0;
    }
    return size;
}
