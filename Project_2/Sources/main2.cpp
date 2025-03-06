#include "server.h"
#include "client.h"
#include <thread>

using namespace std;

int main() {
    server::start();
    server::listen();

    thread t1(client::connect);

    server::stop();
    return 0;
}