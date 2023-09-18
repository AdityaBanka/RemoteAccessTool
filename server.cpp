#include <iostream>
#include <thread>
#include <winsock2.h>

using namespace std;
//hello
class SERVER
{
public:
    int socketFD;
    struct sockaddr_in address;
};
