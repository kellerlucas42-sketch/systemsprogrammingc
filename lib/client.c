#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"
#include "log.h"


int client_connect(const Config *config) {
    // Sets up structs for address info of specified hostname/port pair
    log_info("Connecting to server...");
    struct addrinfo hints, *result, *rp;
    int sockfd = -1;
    int status;

    // Sets the IP version to unspecified to be version neutral and the socket type to TCP
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;     // Either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    // Checks to see if there is correct address info for hostname/port pair
    if ((status = getaddrinfo(config->host, config->port, &hints, &result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // Loops through linked list pairs of info to establish a valid socket
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        // Socket incorrect
        if (sockfd < 0) {
            fprintf(stderr, "%s\n", strerror(ENOTCONN));
            continue;
        }

        // Checks to see if connection is valid
        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            log_info("Connection established");
            break;
        } else {
            fprintf(stderr, "%s\n", strerror(ETIMEDOUT));
            close(sockfd);
            sockfd = -1;
        }
    }

    freeaddrinfo(result); // free the linked list
    if (sockfd == -1) {
        fprintf(stderr, "Could not establish connection with TCP server\n");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

void client_send_image(int sockfd, const Config *config) {
    // IMPLEMENT THIS FUNCTION
    client_connect(const Config *config);
    int socket = sockfd;
    int data_length = Config.payload_size;
    int total_sent = 0
    int num_sent = 0

    uint8_t combine = malloc(sizeof(uint8_t)) * (128*128*3)


    uint8_t *data = Config.payload;




    while (total_sent < data_length){
        num_sent = send(socket, data + total_sent, data_length - total_sent, 0)

        if (num_sent < 0){
            return -1;
        }
    
    total_sent += num_sent
    }


    
}

void client_receive_response(int sockfd) {
    uint8_t buf[101];
    int num_recv = recv(sockfd, buf, 100, 0);
    buf[num_recv] = '\0';

    printf("Response from server: %s\n", buf);
}

void client_close(int sockfd) {
    // IMPLEMENT THIS FUNCTION
}



/*
client_connect();

client_send_image();

client_recieve_response();

client_close();

drawMenublahblahblah


Config.host = ecen224.byu.edu;
Config.port = 2240;
Config.hw_id = "AC61BDF31";
Config.payload = camera_capture_data(buf, bufsize);
Config.payload_size = bufsize; 
*/