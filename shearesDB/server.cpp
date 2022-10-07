#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define size_t socklen_t
void func(int connfd);

int main(){
    size_t sockfd, connfd, len;
    struct sockaddr_in servaddr, client;

    // Create the welcome socket and bind
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        std::cout << "Socket creation failed";
        return 0;
    } else{
        std::cout << "Socket successfully created";
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) != 0){
        std::cout<< " Socket binding has failed";
    }else{
        std::cout<< " Socket succesfully binded";
    }

    if(listen(sockfd, 5) != 0){
        std::cout<<"Socket listening failed";
    }else{
        std::cout<<"Socket is listening......";
    }

    while(true){
        len = sizeof(client);
        connfd = accept(sockfd, (struct sockaddr *) &client, &len);
         if(connfd < 0){
            std::cout<<"Server acceptance Failed";
            return 0;
        }else{
            std::cout<<"Server has accepted the client...\n";
        };
        func(connfd);
        close(connfd);
    }
    close(sockfd);
}


void func(int connfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t \nTo client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        // The getchar() function is equivalent to a call to getc(stdin). It reads the next character from stdin which is usually the keyboard.
        while ((buff[n++] = getchar()) != '\n');
   
        // send buffer to client
        write(connfd, buff, n+1);
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}