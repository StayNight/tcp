#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>


int main(){
    struct sockaddr_in sin, pin;
    int port = 8000;

    int sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_descriptor < 0){
        perror("call to socket");
        exit(EXIT_FAILURE);
    }

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(8001);

    if (bind(sock_descriptor, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        perror("call to bind");
        exit(EXIT_FAILURE);
    }

    if(listen(sock_descriptor, 20) < 0){
        perror("call to listen");
        exit(EXIT_FAILURE);
    }

    while(1){
        int address_size = 0;
        int temp_sock_descriptor = accept(sock_descriptor, (struct sockaddr *)&pin, &address_size);
        if(temp_sock_descriptor < 0){
            perror("call to accept");
            exit(EXIT_FAILURE);
        }

        char buf[16384];
        if(recv(temp_sock_descriptor, buf, 16384, 0) < 0){
            perror("call to recv");
            exit(EXIT_FAILURE);
        }
        printf("received from client : %s\n", buf);

        int len = strlen(buf);
        for(int i = 0; i < len; i++)
            buf[i] = toupper(buf[i]);
    
        if(send(temp_sock_descriptor, buf, len, 0) == -1){
            perror("call to send");
            exit(EXIT_FAILURE);
        }

        close(temp_sock_descriptor);
    }





}