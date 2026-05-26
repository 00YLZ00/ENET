#include <iostream>
#include "Channel.h"
#include "TcpSocket.h"
#include "Timer.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "BufferWriter.h"
#include "BufferReader.h"

#define dg(x) std::cout << #x << "=" << x << '\n';

void test1()
{
    TcpSocket listensock;
    int ret = 0;
    ret = listensock.Create();
    dg(ret);
    ret = listensock.Bind("0.0.0.0", 8080);
    dg(ret);
    ret = listensock.Listen(6);
    dg(ret);
    ret = listensock.Accept();
    dg(ret);
}

void test2()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << "a+b= " << a + b << '\n';
}

void test3()
{
    uint32_t count = std::thread::hardware_concurrency();
    dg(count)
        printf("%d %s\n", __LINE__, __FILE__);
    EventLoop loop(1);
    TcpServer *server = new TcpServer(&loop);
    // bool status = server->Start("192.168.31.30",4836);
    bool status = server->Start("0.0.0.0", 1996);
    std::cout << "server start" << std::endl;
    getchar();
    server->Stop();
    std::cout << "server terminate" << std::endl;
}

void buffer_test()
{
    TcpSocket listensock;
    int ret = 0;
    ret = listensock.Create();
    dg(ret);
    ret = listensock.Bind("0.0.0.0", 8080);
    dg(ret);
    ret = listensock.Listen(6);
    dg(ret);
    int fd = listensock.Accept();
    BufferWriter buffer_writer_;
    BufferReader buffer_reader_;
    while (1)
    {
        buffer_reader_.Read(fd);
        std::string s;
        buffer_reader_.ReadAll(s);
        dg(s)
            buffer_writer_.Append(s.c_str(), s.size());
        buffer_writer_.Send(fd);
    }
}

void Timer_test()
{
    TcpSocket listensock;
    int ret = 0;
    ret = listensock.Create();
    dg(ret);
    ret = listensock.Bind("0.0.0.0", 1996);
    dg(ret);
    ret = listensock.Listen(6);
    dg(ret);
    int fd = listensock.Accept();
    dg(fd)
    BufferWriter buffer_writer_;
    BufferReader buffer_reader_;
    TimerQueue timer_queue_;
    ret = timer_queue_.AddTimer([&buffer_writer_, &fd]()
                                {
        std::string s= "你好，我是服务器"; 
        buffer_writer_.Append(s.c_str(),s.size());
        buffer_writer_.Send(fd);
        return true; }, 1000);
    
    dg(ret)
    while (1)
    {
        timer_queue_.HandleTimerEvent();
    }
}

int main()
{
    char buffer[] = "你好，我是柴永康"; 
    dg(buffer);
    test3();
    return 0;
}