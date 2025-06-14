#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "header.hpp"


int main(){
    std::cout << "<-----hello----->" << std::endl;
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd < 0){
        std::cout << "socker creation failed" << std::endl;
        return -1;
    }

    sockaddr_in address;
    int address_len = sizeof(address);
    memset(&address, 0, sizeof(address));


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(1278);

    if(bind(server_fd, (sockaddr*)&address, sizeof(address))<0){
        std::cout << "Bind failed" << std::endl;
        return -1;
    }
    std::cout << "Server listening on port 1278...\n";

    if(listen(server_fd, 3) < 0){
        std::cout << "Listen failed" << std::endl;
        return -1;
    }

    int new_socket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&address_len);
    
    if (new_socket < 0) {
        std::cout << "Accept failed" << std::endl;
        return 1;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "Connection accepted from " << client_ip << ":" << ntohs(address.sin_port)  << std::endl;
    
    while(true){
    
        char buffer[1024] = {0};
        if (read(new_socket, buffer, 1024) <= 0){
            break;
        }
        std::cout << "Message from client: " << buffer  << std::endl;

        Message message(buffer);
        std::string response = "Get message with id = "+ std::to_string(message.id)+ " from " + message.from + " to " + message.to + " with text: " + message.text;

        send(new_socket, response.c_str(), response.length(), 0);
        std::cout << "Response sent" << std::endl;
    }

    
    close(new_socket);
    close(server_fd);
    return 0;
}
