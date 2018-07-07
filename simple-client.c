#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

char *host_name = "127.0.0.1";

int port = 8000;

void main(int argc, char *argv[])
{
    char buf[8192];
    char message[256];
    int socket_descriptor;
    struct sockaddr_in pin;
    struct hostent * server_host_name;

    char * str = "A default test string";

    if(argc < 2){
        printf("Usage:TestingString\n");
        printf("We will send a default test string.\n");
    }else{
        str = argv[1];
    }

    if((server_host_name = gethostbyname(host_name)) == 0){
        perror("Error resolving local host\n");
        exit(EXIT_FAILURE);
    }

    bzero(&pin, sizeof(pin));
    pin.sin_family = AF_INET;
    pin.sin_addr.s_addr = htonl(INADDR_ANY);
    pin.sin_addr.s_addr = ((struct in_addr *)(server_host_name->h_addr)) \
                            -> s_adddr;
    pin.sin_port = htons(port);

    if(socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error opening socket\n");
        exit(EXIT_FAILURE);
    }

    if(connect(socket_descriptor,(void*)&pin, sizeof(pin)) == -1){
        perror("Error connecting to socket\n");
        exit(EXIT_FAILURE);
    }

    printf("Sending message %s to server...\n", str);
}