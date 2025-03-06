#include "server.h"
#include "client.h"
#include <thread>

using namespace std;

int main() {
    server::start();
    thread t1(client::connect);
    server::listen();

    server::stop();
    return 0;
}