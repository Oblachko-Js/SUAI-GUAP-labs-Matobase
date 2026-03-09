#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h> // Для сокетов
#include <unistd.h>   // Для close()

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

   // Создание сокета
   int sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0) {
       std::cerr << "Error: Unable to create socket." << std::endl;
       return EXIT_FAILURE;
   }

   struct sockaddr_in server_addr;
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port);
   
   // Преобразование IP-адреса
   if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
       std::cerr << "Error: Invalid address or address not supported." << std::endl;
       close(sock);
       return EXIT_FAILURE;
   }

   // Подключение к серверу
   if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
       std::cerr << "Error: Connection failed." << std::endl;
       close(sock);
       return EXIT_FAILURE;
   }

   char buffer[1024];

   while (true) {
       memset(buffer, 0, sizeof(buffer)); // Очистка буфера перед использованием

       // Получаем сообщение от сервера
       int recv_len = recv(sock, buffer, sizeof(buffer) - 1, 0);
       
       if (recv_len > 0) {
           buffer[recv_len] = '\0'; // Добавляем нуль-терминатор для корректного отображения строки
           std::cout << "\nServer response: " << buffer;

           // Ввод логина и пароля
           std::string input;
           std::cout << "Enter username and password (format: username password) or -1 to exit: ";
           std::getline(std::cin, input);

           // Проверяем на выход
           if (input == "-1") break;

           // Отправляем данные на сервер
           send(sock, input.c_str(), input.size(), 0);
       } else if (recv_len == 0) {
           std::cout << "Server closed the connection." << std::endl;
           break; // Сервер закрыл соединение
       } else {
           std::cerr << "Error: Failed to receive response from server." << std::endl;
           break; 
       }
   }

   close(sock); // Закрываем сокет

   return EXIT_SUCCESS; 
}
