#include <iostream>
#include <thread>

using namespace std;

void startup() {
    int num_of_clients = 0;

    cout << "Set number of clients: ";
    cin >> num_of_clients;
    cin.ignore();

    for (int i = 0; i < num_of_clients; i++) {
        string command = "start cmd /k client.exe " + to_string(i + 1);
        system(command.c_str());
    }
}

int main() {
    startup();

    return 0;
}
