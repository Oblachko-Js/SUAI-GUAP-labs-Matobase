// Copyright 2024 <Андрей Панченко>

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <thread>

// Function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Function to convert numbers to words in English
std::string number_to_words(int num) {
    if (num == 0) return "zero";

    std::vector<std::string> below_20 = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight",
        "nine", "ten", "eleven", "twelve",
        "thirteen", "fourteen", "fifteen",
        "sixteen", "seventeen",
        "eighteen", "nineteen"
    };

    std::vector<std::string> tens = {
        "", "",
        "twenty",
        "thirty",
        "forty",
        "fifty",
        "sixty",
        "seventy",
        "eighty",
        "ninety"
    };

    std::string words;

    if (num >= 1000) {
        words += number_to_words(num / 1000) + " thousand ";
        num %= 1000;
    }

    if (num >= 100) {
        words += below_20[num / 100] + " hundred ";
        num %= 100;
    }

    if (num >= 20) {
        words += tens[num / 10] + (num % 10 ? "-" + below_20[num % 10] : "");
    } else if (num > 0) {
        words += below_20[num];
    }

    return words;
}

bool is_valid_number(const std::string& str) {
    if (str.empty() || str[0] == '-') return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Function to handle client requests in a separate thread
void handle_client(int sockfd, struct sockaddr_in client_addr, socklen_t addr_len, std::string received_str) {
    if (!is_valid_number(received_str)) {
        std::cerr << "[Server] Invalid input received: " << received_str << std::endl;
        return;
    }

    int received_number = std::stoi(received_str);
    bool prime = is_prime(received_number);
    std::string response = std::to_string(prime) + ' ' + number_to_words(received_number);

    // Send response back to the client
    if (sendto(sockfd, response.c_str(), response.size(), 0, (struct sockaddr*)&client_addr, addr_len) < 0) {
        std::cerr << "[Server] Error sending response." << std::endl;
    }

    std::cout << "[Server] Received number: " << received_number << ", Sending response: " << response << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Incorrect number of arguments. Expected port number as argument." << std::endl;
        return EXIT_FAILURE;
    }

    int port;
    try {
        port = std::stoi(argv[1]);
        if (port <= 0 || port > 65535) {
            std::cerr << "Error: Port number out of range (1-65535)." << std::endl;
            return EXIT_FAILURE;
        }
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid argument. Not a number." << std::endl;
        return EXIT_FAILURE;
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Argument out of range." << std::endl;
        return EXIT_FAILURE;
    }

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sockfd < 0) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_addr.sin_port = htons(port);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Unable to bind socket." << std::endl;
        close(sockfd);
        return EXIT_FAILURE;
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        
        ssize_t received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);
        
        if (received_bytes < 0) {
            std::cerr << "[Server] Error: Unable to receive data." << std::endl;
            continue;
        }

        // Convert buffer to string
        std::string received_str(buffer);

        // Start a new thread to handle the client
        std::thread client_thread(handle_client, sockfd, client_addr, addr_len, received_str);
        client_thread.detach(); // Detach the thread so it runs independently
    }

    close(sockfd);
    return EXIT_SUCCESS;
}
