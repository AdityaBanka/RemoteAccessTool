#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

/*
We will be using this structure to set state variables for internal tooling
mostly used for debugging the code and providing crude functionality inside
the code such as, state of printing, baud rate, and other related capabilities.
*/
struct CLIENT_STATE
{
    int printing_state; // 0 - disable, 1 - enable
} clientState;

void initialize_WSA_API()
{
    printf("Initializing WSA startup..\n");
    printf("1. WSA startup :\t");
    WSADATA wsaData;
    int returnValue = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (returnValue != 0)
    {
        printf("Failed due->%d\n", returnValue);
        return;
    }
    printf("Successful\n");
    printf("\n");
    return;
}

SOCKET createSocket(char *IP_Address, int portNumber)
{
    // creating the socket
    printf("Initializing socket..\n");
    printf("1. Socket Creation :\t");
    SOCKET socketFD = INVALID_SOCKET;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == INVALID_SOCKET)
    {
        printf("Failed due->%d\n", WSAGetLastError());
        WSACleanup();
        return (0);
    }
    printf("Successful\n");

    // connecting to the server
    printf("2. Connecting :\t");
    struct sockaddr_in address;
    address.sin_addr.s_addr = inet_addr(IP_Address);
    address.sin_family = AF_INET;
    address.sin_port = hton(portNumber);
    int returnValue = connect(socketFD, (struct sockaddr *)&address, sizeof(address));
    if (returnValue == SOCKET_ERROR)
    {
        printf("Failed due->%d\n", WSAGetLastError());
        WSACleanup();
        return (0);
    }
    printf("Successful\n");
    return (socketFD);
}

int main()
{
    clientState.printing_state = 1;

    //getting the socket
    printf("Creating socket..\n");
    SOCKET socketFD = createSocket("127.0.0.1", 8000);
    printf("3. Receiving :\t");
    if(socketFD == 0)
    {
        printf("Failed\n");
    }
    printf("Successful\n");
    printf("Socket is successfully created, connected and received\n");
    closesocket(socketFD);
    WSACleanup();

    return 0;
}
