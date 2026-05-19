#include <string>

class SocketUtil
{
public:
    static void SetNonBlock(int sockfd);
    static void SetBlock(int sockfd);
    static void SetReuseAddr(int sockfd);
    static void SetReusePort(int sockfd);
    static void SetKeepAlive(int sockfd);
    static void SetSendBufSize(int sockfd, int size);
    static void SetRecvBufSize(int sockfd, int size);
};

class TcpSocket
{
private:
    /* data */
    int sockfd_ = -1;

public:
    TcpSocket(/* args */);
    virtual ~TcpSocket();

public:
    int Create();
    bool Bind(std::string ip, short port);
    bool Listen(int backlog);
    int Accept();
    void Close();
    void ShutdownWrite();
    int GetSocket() const
    {
        return sockfd_;
    }
};
