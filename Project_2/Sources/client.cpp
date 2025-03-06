//
// Created by mateu on 06.03.2025.
//
#include <iostream>
#include <winsock2.h>
#include <client.h>
#include <thread>

using namespace std;

namespace client {
    void connect() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "WSAStartup failed!" << endl;
            return;
        }

        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Client's socket creation failed!" << endl;
            WSACleanup();
            return;
        }


        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

        try {
            connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
        } catch (...) {
            cout << "Client's connection failed!" << endl;
            WSACleanup();
            return;
        }


        const char *message = "Hello, I am client!";
        send(clientSocket, message, strlen(message), 0);

        closesocket(clientSocket);
        WSACleanup();
    }
}