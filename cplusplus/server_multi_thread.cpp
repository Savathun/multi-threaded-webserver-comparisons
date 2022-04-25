//
//  server_multit_thread.cpp
//  Web Server V1
//
//  Created by Julian Roberts Michael Hoover.
//

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

// #include "server.hpp"

#define PORT 8080

pthread_t tid[100];


typedef struct {
 int a_socket;
} arg_t;

void* send_msg_thread(void *args)
{
    arg_t *thread_args = (arg_t *) args;
    const char *base_msg = "Hello to thread";

    // read buffer
    char buffer[30000] = {0};

    long valread = read(thread_args->a_socket, buffer, 30000);
    std::cout << std::endl
                << buffer
                << std::endl;
    //send message
    
    write(thread_args->a_socket, base_msg, strlen(base_msg));
    std::cout << "Message sent." << std::endl;
    sleep(1);
        
    close(thread_args->a_socket);
}

int main(int argc, char const *argv[])
{
    // define vars
    int server_fd, new_socket;
    const char *base_msg = "Hello to thread";

    struct sockaddr_in address;
    int address_length = sizeof(address);

    // ---

    // create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "In socket." << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "In bind" << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 40) < 0)
    {
        std::cout << "In listen" << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    //thread array, max 100
    int i = 0;

    // listening for connections
    while (true)
    {
        std::cout << std::endl
                  << "======= Waiting for new connection ========"
                  << std::endl
                  << std::endl;

        // error check
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&address_length)) < 0)
        {
            std::cout << "In accept" << std::strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }

        arg_t args = { new_socket };

        //create thread to handle new client
        if (pthread_create(&tid[i++], NULL, send_msg_thread, &args) != 0)
        {
            printf("ERROR: thread creation failed!");
        }
        
    }
    return 0;
}
