#include <iostream>
#include "Channel.h"
#include "TcpSocket.h"
#include "Timer.h"
#include "EventLoop.h"
#include "TcpServer.h"

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
}


int main()
{
    uint32_t count = std::thread::hardware_concurrency();
    dg(count)
    printf("%d %s\n",__LINE__,__FILE__);
    EventLoop loop(2);
    TcpServer *server = new TcpServer(&loop);
    // bool status = server->Start("192.168.31.30",4836);
    bool status = server->Start("0.0.0.0", 1996);
    std::cout << "server start" << std::endl;
    getchar();
    server->Stop();
    std::cout << "server terminate" << std::endl;
    return 0;
}