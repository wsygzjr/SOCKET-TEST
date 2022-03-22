#include "ThreadTest.h"
using namespace std;
#pragma   comment(lib, "Ws2_32.lib")

bool init_Socket()
{
    //socket版本，传出参数
    WSADATA wsadata;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
    {
        cout << "WSAStartup failed" << endl;
        return false;
    }
    return true;
}


bool close_Socket()
{
    if (0 != WSACleanup())
    {
        cout << "WSACleanup" << endl;
        return false;
    }
    return true;
}

SOCKET CreateServerSocket()
{
    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in seraddr;
    memset(&seraddr, 0, sizeof(seraddr));

    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8008);
    //inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.S_un.S_addr);
    seraddr.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(server, (sockaddr*)&seraddr, sizeof(seraddr));

    return server;
}

void rec(SOCKET con)
{
    char buf[1024] = { '1','2','3','4','5','6','7','8','9','0','\0' };
    while (true)
    {
        memset(buf, 0, 1024);
        // if(0 < recv(con, buf, 0, 0))
        recv(con, buf, 1024, 0);
        cout << buf << endl;
    }
}

void sen(SOCKET con)
{
    char buf[1024] = { '1','2','3','4','5','6','7','8','9','0','\0' };
    while (true)
    {
        memset(buf, 0, 1024);
        // if(0 < recv(con, buf, 0, 0))
        cin >> buf;
        send(con, buf, 1024, 0);
        //cout << buf << endl;
    }
}

int main()
{
    init_Socket();

    SOCKET server = CreateServerSocket();
    SOCKET con;

    listen(server, 5);

    struct sockaddr_in connect;
    memset(&connect, 0, sizeof(connect));

    int conlen = sizeof(connect);

    //memset(buf, 0, 1024);
    con = accept(server, (sockaddr*)&connect, &conlen);

    thread th1(rec, con);
    //thread th2(sen, con);
    th1.detach();    
    //th2.join();
    sen(con);

    closesocket(con);
    closesocket(server);
    close_Socket();
}
