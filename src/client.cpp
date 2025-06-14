#include <cstdio>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "header.hpp"



int main(){

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(1278);
    

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported\n";
        return 1;
    }


    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    std::cout << "Connected to server\n";


    while(true){
        std::string id, from, to, text, flag;
        std::cout << "exit? >";
        std::getline(std::cin, flag);
        if(flag == "exit"){
            break;
        }
        std::cout << "id >";
        std::getline(std::cin, id);
        std::cout << "from >";
        std::getline(std::cin, from);
        std::cout << "to >";
        std::getline(std::cin, to);
        std::cout << "text >";
        std::getline(std::cin, text);

        Message message(std::stoi(id), from, to, text);
        std::string message_string = message.to_string();
        
        send(sock, message_string.c_str(), message_string.length(), 0);
        std::cout << "Message sent\n";
        char buffer[1024] = {0};
        read(sock, buffer, 1024);
        std::cout << "Server response: " << buffer << "\n";
    }

    close(sock);
    return 0;
}