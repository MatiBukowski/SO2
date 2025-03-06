#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

namespace client {
    mutex display_mutex;

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
            ::connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
        } catch (...) {
            cout << "Client's connection failed!" << endl;
            WSACleanup();
            return;
        }

        display_mutex.lock();
        cout << "Client connected to server!" << endl;
        display_mutex.unlock();

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

        closesocket(clientSocket);
        WSACleanup();
    }
}

int main() {
    // int num_of_clients = 0;
    // vector<thread> clients;
    //
    // cout << "Set number of clients: ";
    // cin >> num_of_clients;
    // cin.ignore();
    //
    // for(int i = 0; i < num_of_clients; i++) {
    //     // clients.emplace_back(client::connect, i+1);
    //     string command = "start cmd /k client.exe " + to_string(i + 1);
    //     system(command.c_str());
    // }
    //
    // for (thread &t : clients) {
    //     t.join();
    // }
    //
    // return 0;
    client::connect();
}