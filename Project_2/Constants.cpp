#include <string>
#include <iostream>

static const std::string WSASTARTUP_FAILURE = "WSAStartup failed!";
static const std::string CREATE_FAILURE = "Socket creation failed!";
static const std::string CONNECTION_FAILURE = "Connection failed!";
static const std::string BIND_FAILURE = "Bind failed!";
static const std::string LISTEN_FAILURE = "Listen failed!";
static const std::string ACCEPT_FAILURE = "Accept failed!";

static void send_error_message(std::string errorMessage) {
    std::cout << errorMessage << std::endl;
}
