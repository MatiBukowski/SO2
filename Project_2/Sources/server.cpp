//
// Created by mateu on 06.03.2025.
//

//
// Created by mateu on 06.03.2025.
//
#include <iostream>
#include <winsock2.h>
#include <server.h>
#include <thread>

using namespace std;

int serverSocket;

namespace server {
    void start() {
        WSADATA wsaData;                                    // before using windows socket we have to initialize this function. It is used to initialized Windows Socket API
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "WSAStartup failed!" << endl;
            return;
        }

        // Creating server socket
        serverSocket = socket(AF_INET, SOCK_STREAM,
                              0);         // AF_INET - IPv4 protocol family, SOCK_STREAM - TCP type socket

        if (serverSocket == INVALID_SOCKET) {
            cout << "Socket creation failed!" << endl;
            WSACleanup();
            return;
        }

        // Defining server address
        sockaddr_in serverAddress;                                         // sockaddr_in - data type that is used to store the address of the socket

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(
                8080);                      // htons - function is used to convert the unsigned int from machine byte order to network byte order
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");                        // INADDRY_ANY - used when we don't want to bind our socket to any particular IP and instead make it listen to all the available IPs

        // Binding the server socket
        try {
            bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
        } catch (...) {
            cout << "Bind failed!" << endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        cout << "Server started on port: 8080" << endl;
    }

    void stop() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void listen() {
            try {
                // 5 - max amount od devices waiting for connection, application listen to the socket referred by the serverSocket
                ::listen(serverSocket, 5);
            } catch (...) {
                cout << "Listen failed!" << endl;
                closesocket(serverSocket);
                WSACleanup();
                return;
            }

            // Accepting a client connection
            // used to accept the connection request that is recieved on the socket the application was listening to
            int clientSocket = accept(serverSocket, nullptr, nullptr);

            if (clientSocket == INVALID_SOCKET) {
                cout << "Accept failed!" << endl;
                closesocket(serverSocket);
                WSACleanup();
                return;
            }

            // Receiving Data from the Client
            char buffer[1024] = {0};
            recv(clientSocket, buffer, sizeof(buffer), 0);
            cout << "Message from client: " << buffer << endl;
        }
}
