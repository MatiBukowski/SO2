#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

namespace client {
    int clientSocket;
    mutex displayMutex;

    void connect() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "WSAStartup failed!" << endl;
            return;
        }

        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
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
            ::connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
        } catch (...) {
            cout << "Client's connection failed!" << endl;
            WSACleanup();
            return;
        }

        // display_mutex.lock();
        cout << "Client connected to server!" << endl;
        cout << "Chat:" << endl << endl;
        // display_mutex.unlock();
    }

    void stop() {
        closesocket(clientSocket);
        WSACleanup();
    }

    void send_message() {
        // Sending Message to Server
        string message_str;
        const char* message;

        while(true) {
            // display_mutex.lock();
            // cout << "Client " << client_id << ": ";
            // display_mutex.unlock();
            getline(cin, message_str);
            // display_mutex.unlock();

            if (message_str == "exit") {
                message = message_str.c_str();                                      // convert string to const char*
                send(clientSocket, message, strlen(message), 0);
                break;
            }

            message = message_str.c_str();                                          // convert string to const char*
            send(clientSocket, message, strlen(message), 0);
        }
    }

    void receive_messages() {
        HANDLE console_color;                               // console handler for text's color change
        console_color = GetStdHandle(STD_OUTPUT_HANDLE);


        char buffer[1024];

        while(true) {
            memset(buffer, 0, sizeof(buffer));

            try {
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

                if(bytesReceived > 0) {
                    int color = buffer[5] - '0' + 1;                                  // user number (covert to int) + 1 (like in server)
                    SetConsoleTextAttribute(console_color, color);                    // set color

                    displayMutex.lock();
                    cout << buffer << endl;
                    displayMutex.unlock();

                    SetConsoleTextAttribute(console_color, 15);             // set white color back
                }
            } catch (...) {}
        }
    }
}

int main() {
    client::connect();
    thread t_send(client::send_message);
    thread (client::receive_messages).detach();

    t_send.join();
    client::stop();
    return 0;
}
