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
    int printing_state; //0 - disable, 1 - enable
}clientState;

void initialize_WSA_API()
{
    WSADATA wsaData;
    int returnValue = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(returnValue != 0)
    {
        printf("%d : WSA startup : failed.\n", returnValue);
        return;
    }
    else
    {
        printf("WSA successfully initialized.\n");
    }
    return;
}

void createClient(char *IP_Address, int portNumber)
{
    printf("Initializing socket..\n");
    struct sockaddr_in address;
    address.sin_addr.s_addr = inet_addr(IP_Address);
    address.sin_family = AF_INET;
    address.sin_port = hton(portNumber);

    printf("1. Socket Creation : ");
    SOCKET socketFD = INVALID_SOCKET;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD == INVALID_SOCKET)
    {
        printf("Failed due->%d\n", WSAGetLastError());
        WSACleanup();
        return;
    }
}

int main()
{
    clientState.printing_state = 1;

    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serverAddr;

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    int ret = connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret == SOCKET_ERROR)
    {
        std::cerr << "Connect failed: " << WSAGetLastError() << "\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to the server!\n";

    // Clean up and close the socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
