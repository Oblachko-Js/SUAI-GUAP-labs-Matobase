// Copyright 2024 Щукин А.А. 4236
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <cctype>


#define PORT 8080
#define BUFFER_SIZE 1024

std::string get_date() {
    std::time_t now = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S%z", std::localtime(&now));
    return std::string(buffer);
}

std::string get_process_list() {
    std::string result;
    DIR *dir = opendir("/proc");
    if (!dir) {
        return "Failed to read /proc directory";
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string pid = entry->d_name;
            if (std::all_of(pid.begin(), pid.end(), ::isdigit)) {
                std::ifstream cmdline("/proc/" + pid + "/cmdline");
                std::string cmd;
                std::getline(cmdline, cmd, '\0');
                if (!cmd.empty()) {
                    result += pid + ": " + cmd + "\n";
                }
            }
        }
    }
    closedir(dir);
    return result;
}

void handle_client(int sockfd, struct sockaddr_in client_addr, socklen_t addr_len) {
    char buffer[BUFFER_SIZE];
    while (true) {
        std::memset(buffer, 0, BUFFER_SIZE);
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
  std::cerr << recv_len << std::endl;
        if (recv_len < 0) {
            std::cerr << "Server error: Error receiving data" << std::endl;
            continue;
        }

        std::string command(buffer);
  std::cerr << "Received command: " << command << std::endl;
        std::string response;
        
        if (command == "date") {
            response = get_date();
        } else if (command == "ps") {
            response = get_process_list();
        } else if (command == "quit") {
            response = "Server shutting down.";
            sendto(sockfd, response.c_str(), response.size(), 0, (struct sockaddr*)&client_addr, addr_len);
            break;
        } else {
            response = "Unknown command";
        }

        sendto(sockfd, response.c_str(), response.size(), 0, (struct sockaddr*)&client_addr, addr_len);
    }

    std::cout << "Server shutdown." << std::endl;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    std::cout << "Server is running on port " << PORT << std::endl;

    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    handle_client(sockfd, client_addr, addr_len);

    return 0;
}

