#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <shearesDB.hpp>
#include <vector>
#define MAX 80
#define PORT 8080
#define size_t socklen_t
void router(int connfd, shearesDB& db);
void getHandler();
void putHandler();

int main(){
    size_t sockfd, connfd, len;
    struct sockaddr_in servaddr, client;
    shearesDB db;
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
        router(connfd,db);
        close(connfd);
    }
    close(sockfd);
}


void router(int connfd, shearesDB& db){
    uint32_t dataLen;
    char buff[MAX];
    bzero(buff, MAX);
    uint16_t opCode;
    read(connfd, &dataLen, sizeof(dataLen));
    read(connfd, &opCode, sizeof(opCode));

    char key[dataLen-2];
    read(connfd, &key, sizeof(key));
    std::vector<char> res =  getHandler(key, db);
    int resSize = res.size();
    char outputBuff[resSize];

    bzero(outputBuff, resSize);
    for(int i = 0; i < resSize; i++){
        outputBuff[i] = res[i];
    }

   
        // send buffer to client
    write(connfd, outputBuff, resSize);

}

std::vector<char> getHandler(char* key, shearesDB& db){
    std::string keyStr(key);
    return db.get(keyStr);
}

// void putHandler(){

// }