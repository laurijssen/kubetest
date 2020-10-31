#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#include "httpheader.h"

#define PORT 8080

static int count = 1;
static int rnd;

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    char hello[1024];

    srand(time(NULL));
    rnd = rand() % 500;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
        
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        printf("listen failed\n");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\nWaiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            printf("Erroring out\n");
            exit(EXIT_FAILURE);
        }
                
        char buffer[30000] = {0};
        valread = read(new_socket , buffer, 30000);
        printf("%s\n", buffer);

        HTTPREQUEST *req = InitHeaders();

        AddHeader(req, "HTTP/1.1 200 OK\n");
        AddHeader(req, "Content-Type: text/plain\n");

        sprintf(hello, "Again from %d %d\n", rnd, count++);
        
        SetBody(req, hello);
        Write(req,new_socket);

        close(new_socket);
        DestroyHeaders(req);
    }
    return 0;
}
