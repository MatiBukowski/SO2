#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include "Constants.cpp"

using namespace std;

namespace server {
    void read(int);
    void send(int);

    mutex displayMutex;
    int serverSocket;

    void stop() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void bind() {
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
        while(true) {
            try {
                // 5 - max amount od devices waiting for connection, application listen to the socket referred by the serverSocket
                ::listen(serverSocket, 5);
            } catch (...) {
                send_error_message(LISTEN_FAILURE);
                server::stop();
                return;
            }
        }
    }

    void accept(){
        // Accepting a client connection
        // used to accept the connection request that is recieved on the socket the application was listening to
        while(true) {
            int clientSocket = ::accept(serverSocket, nullptr, nullptr);

            if (clientSocket == INVALID_SOCKET) {
                send_error_message(ACCEPT_FAILURE);
                continue;
            }

            cout << "Client connected!" << endl;
            thread(read, clientSocket).detach();
        }
    }

    void send(int clientSocket, const char* message){
        int bytesSent;
        char sendbuf[ 32 ] = "Client says hello!";
        cout << "bump" << endl;
        ::send(clientSocket, message, strlen(message), 0);
    }

    void read(int clientSocket) {
        int bytesRecv = SOCKET_ERROR;
        char recvbuf[ 32 ] = "";

        while( bytesRecv == SOCKET_ERROR )
        {
            bytesRecv = recv( clientSocket, recvbuf, 32, 0 );

            if( bytesRecv == 0 || bytesRecv == WSAECONNRESET ){
                break;
            }

            if( bytesRecv < 0 )
                return;

            cout << recvbuf << endl;
        }

    }

    void start() {
        server::bind();
        thread t_listen(server::listen);
        thread t_accept(server::accept);
    }

}

int main() {
    server::start();
    server::stop();
    return 0;
}
