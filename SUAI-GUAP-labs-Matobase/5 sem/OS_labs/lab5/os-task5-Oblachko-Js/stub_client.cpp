// stub_client.cpp
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback address

    std::string message = "Hello from stub client!";
    
    // Отправляем сообщение на сервер
    sendto(sockfd, message.c_str(), message.size(), 0,
           (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Получаем ответ от сервера
    socklen_t addr_len = sizeof(server_addr);
    ssize_t received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                       (struct sockaddr*)&server_addr, &addr_len);
    
    if (received_bytes > 0) {
        buffer[received_bytes] = '\0'; // Добавляем нуль-терминатор для корректного отображения строки
        std::cout << "Server response: " << buffer << std::endl;
    } else {
        std::cerr << "Error receiving response from server." << std::endl;
    }

    close(sockfd);
    return EXIT_SUCCESS;
}
