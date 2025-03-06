//
// Created by mateu on 06.03.2025.
//
#include <iostream>
#include <winsock2.h>
#include <connection.h>
#include <thread>

using namespace std;

void clinet_socket_connection();

void main_socket_server_connection() {
    thread client(clinet_socket_connection);
    WSADATA wsaData;                                    // before using windows socket we have to initialize this function
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed!" << endl;
        return;
    }

    // thread client(clinet_socket_connection);

    // Creating server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);         // AF_INET - IPv4 protocol family, SOCK_STREAM - TCP type socket

    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed!" << endl;
        WSACleanup();
        return;
    }

    // Defining server address
    sockaddr_in serverAddress;                                         // sockaddr_in - data type that is used to store the address of the socket

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);                      // htons - function is used to convert the unsigned int from machine byte order to network byte order
    serverAddress.sin_addr.s_addr = INADDR_ANY;                        // INADDRY_ANY - used when we don't want to bind our socket to any particular IP and instead make it listen to all the available IPs

    // Binding the server socket
    try {
        bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    } catch (exception& e) {
        cout << "Bind failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Listening for connections
    try {
        listen(serverSocket, 5);                                            // 5 - max amount od devices waiting for connection, application listen to the socket referred by the serverSocket
    } catch (exception& e) {
        cout << "Listen failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Accepting a client connection
    int clientSocket = accept(serverSocket, nullptr, nullptr);      // used to accept the connection request that is recieved on the socket the application was listening to

    if(clientSocket == INVALID_SOCKET) {
        cerr << "Accept failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Receiving Data from the Client
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Message from client: " << buffer << endl;

    closesocket(serverSocket);
    WSACleanup();

    client.join();
}

void clinet_socket_connection() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed!" << endl;
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
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    try {
        connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    } catch (exception& e) {
        cout << "Client's connection failed!" << endl;
        WSACleanup();
        return;
    }


    const char* message = "Hello, I am client!";
    send(clientSocket, message, strlen(message), 0);

    closesocket(clientSocket);
    WSACleanup();
}
