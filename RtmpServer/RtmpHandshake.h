#include "../EdoyunNet/BufferReader.h"

void WriteUint32BE(char* p,uint32_t value);



class RtmpHandshake
{
public:
    enum State
    {
        HANDSHACK_C0C1,
        HANDSHACK_S0S1S2,
        HANDSHACK_C2,
        HANDSHACK_COMPLETE
    };

private:
    State handshake_state_;

public:
    RtmpHandshake(State state);
    virtual ~RtmpHandshake();

    int Parse(BufferReader &in_buffer, char *res_buf, uint32_t res_buf_size);
    bool IsCompleted() const
    {
        return handshake_state_ == HANDSHACK_COMPLETE;
    }
    int BuildC0C1(char *buf, uint32_t buf_size);
};
