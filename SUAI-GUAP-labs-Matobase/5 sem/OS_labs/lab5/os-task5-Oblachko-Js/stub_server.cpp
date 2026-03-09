// stub_server.cpp
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback address
    server_addr.sin_port = htons(12345);

    // Привязываем сокет к адресу
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(sockfd);
        return EXIT_FAILURE;
    }

    std::cout << "Stub server running on port 12345..." << std::endl;

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        
        // Получаем сообщение от клиента
        ssize_t received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                           (struct sockaddr*)&client_addr, &addr_len);
        
        if (received_bytes < 0) {
            std::cerr << "Error receiving data." << std::endl;
            continue; // Продолжаем слушать дальше
        }

        std::cout << "Received message: " << buffer << std::endl;

        // Отправляем ответ обратно клиенту
        sendto(sockfd, buffer, received_bytes, 0,
               (struct sockaddr*)&client_addr, addr_len);
    }

    close(sockfd);
    return EXIT_SUCCESS;
}
