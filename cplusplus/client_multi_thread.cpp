//
//  client.cpp
//  Web Server V1
//
//  Created by Julian Roberts and Michael Hoover.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

// #include "client.hpp"

#define PORT 8080

void* client_thread(void* args)
{
    
    // define vars
    int sock = 0;
    long valread;

    struct sockaddr_in server_address;
    char const *msg = "Hello from client!";

    // create the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket creation error.\n";
        exit(EXIT_FAILURE);
    }

    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        std::cout << "Invalid address.\n";
        exit(EXIT_FAILURE);
    }
    // try to connect
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cout << "Connection Failed.\n";
        exit(EXIT_FAILURE);
    }
    // send message
 

    char buffer[1024] = {0};
    send(sock, msg, strlen(msg), 0);
    std::cout << "Message sent." << std::endl;
    // read buffer
    valread = read(sock, buffer, 1024);
    std::cout << std::endl
              << buffer
              << std::endl;


    return 0;
}

pthread_t tid[100];

int main(int argc, char const *argv[])
{

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&tid[i], NULL, client_thread, NULL);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
