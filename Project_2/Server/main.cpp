#include <iostream>
#include <winsock2.h>
#include <thread>
#include "Constants.cpp"

using namespace std;

namespace server {
    int serverSocket;

    void stop() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void start() {
        // before using windows socket we have to initialize this function. It is used to initialized Windows Socket API
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            send_error_message(WSASTARTUP_FAILURE);
            return;
        }

        // Creating server socket
        // AF_INET - IPv4 protocol family, SOCK_STREAM - TCP type socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            send_error_message(CREATE_FAILURE);
            server::stop();
            return;
        }

        // Defining server address
        // sockaddr_in - data type that is used to store the address of the socket
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        // htons - function is used to convert the unsigned int from machine byte order to network byte order
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        // Binding the server socket
        try {
            bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
        } catch (...) {
            send_error_message(BIND_FAILURE);
            server::stop();
            return;
        }

        cout << "Server started on port: 8080" << endl;
    }

    void listen() {
        try {
            // 5 - max amount od devices waiting for connection, application listen to the socket referred by the serverSocket
            ::listen(serverSocket, 5);
        } catch (...) {
            send_error_message(LISTEN_FAILURE);
            server::stop();
            return;
        }

        // Accepting a client connection
        // used to accept the connection request that is recieved on the socket the application was listening to
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            send_error_message(ACCEPT_FAILURE);
            server::stop();
            return;
        }

        cout << "Client connected!" << endl;

        // Receiving Data
        char buffer[1024] = {0}; // Buffer to store received data
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            cout << "Message from client: " << buffer << endl;
        } else {
            cout << "Error receiving message from client!" << endl;
        }

        closesocket(clientSocket);
    }
}

int main() {
    server::start();
    server::listen();
    server::stop();
}
