// Copyright 2024 Щукин А.А. 4236
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    // Initialize WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing WinSock" << std::endl;
        return 1;
    }

    // Create socket
    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server successfully." << std::endl;

    char buffer[BUFFER_SIZE];
    while (true) {
        std::string command;
        std::cout << "Enter command (date, ps, quit): ";
        std::getline(std::cin, command);

        // Check if user wants to quit
        if (command == "quit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        // Send command to server
        int send_result = send(sockfd, command.c_str(), command.size(), 0);

        if (send_result == SOCKET_ERROR) {
            std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Receive response from server
        std::memset(buffer, 0, BUFFER_SIZE);
        int recv_len = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (recv_len == SOCKET_ERROR) {
            std::cerr << "Error receiving data: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "Server response: " << buffer << std::endl;
    }

    closesocket(sockfd);
    WSACleanup();

    std::cout << "Client shut down." << std::endl;
    return 0;
}

