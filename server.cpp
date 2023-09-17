#include <iostream>
#include <thread>
#include <winsock2.h>

using namespace std;

class SERVER
{
public:
    int socketFD;
    struct sockaddr_in address;
};
