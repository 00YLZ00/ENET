#include <iostream>
#include "Channel.h"
#include "TcpSocket.h"
#include "Timer.h"

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

int main()
{
    
    return 0;
}