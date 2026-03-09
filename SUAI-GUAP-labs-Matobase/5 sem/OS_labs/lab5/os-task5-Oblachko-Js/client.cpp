// Copyright 2024 <Андрей Панченко>

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // For inet_addr
#include <string>

#pragma comment(lib, "ws2_32.lib")

bool is_valid_number(const std::string& str) {
    // Проверка, является ли строка положительным целым числом или -1
    if (str.empty()) return false; // Пустая строка не является допустимым числом

    if (str == "-1") return true; // Разрешаем -1 для выхода

    for (char c : str) {
        if (!isdigit(c)) { // Если символ не цифра
            return false;
        }
    }
    return true; // Если все символы цифры, то это валидное число
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP address or domain name> <port>" << std::endl;
        return EXIT_FAILURE;
    }

    const char* server_ip = argv[1];
    int port;

    try {
        port = std::stoi(argv[2]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Error: Port number out of range (1-65535)." << std::endl;
            return EXIT_FAILURE;
        }
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid port number." << std::endl;
        return EXIT_FAILURE;
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Port number out of range." << std::endl;
        return EXIT_FAILURE;
    }

    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    // Use inet_pton to set the server IP address or domain name
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        // If inet_pton fails, try to resolve the domain name
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET; // IPv4
        hints.ai_socktype = SOCK_DGRAM;

        if (getaddrinfo(server_ip, nullptr, &hints, &res) != 0) {
            std::cerr << "Error: Unable to resolve hostname." << std::endl;
            closesocket(sock);
            WSACleanup();
            return EXIT_FAILURE;
        }

        server_addr = *(struct sockaddr_in*)res->ai_addr; // Get the first result
        freeaddrinfo(res); // Free the linked list
    }

    std::string input;

    while (true) {
        std::cout << "Enter a number (or -1 to exit): ";
        std::cin >> input;

        // Проверяем введенное значение на валидность
        if (!is_valid_number(input)) {
            std::cout << "Invalid input. Please enter a positive integer or -1 to exit." << std::endl;
            continue; // Запрашиваем ввод снова
        }

        int number = std::stoi(input); // Преобразуем строку в число

        if (number == -1) break; // Выход из цикла

        // Отправляем число на сервер
        sendto(sock, input.c_str(), input.size(), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));
        
        // Получаем ответ от сервера
        int recv_len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
        buffer[recv_len] = '\0'; // Добавляем нуль-терминатор для корректного отображения строки
        
        std::cout << "Server response: " << buffer << std::endl;
    }

    // Закрываем сокет и очищаем Winsock
    closesocket(sock);
    WSACleanup();
    
    return 0;
}
