#include "../lib/common.h"

void send_data(int fd){
    char buffer[BUFSIZ*10];
    bzero(buffer, sizeof(buffer));
    char c = 'A';
    for(int i = 0; i < sizeof(buffer); i++){
        buffer[i] = c++;
        if(c > 'Z'){
            c = 'A';
        }
    }
    int remain = sizeof(buffer);
    char* pos = buffer;
    while(remain > 0){
        int n = send(fd, pos, BUFSIZ, 0);
        printf("send %dB data\n", n);
        if (n <= 0){
            error(-1, errno, "send error");
            return ;
        }
        remain = remain - n;
        pos = pos + n;
    }
}

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in sock;
    bzero(&sock, sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &sock.sin_addr);
    connect(sockfd, (struct sockaddr*)&sock, sizeof(sock));
    send_data(sockfd);    
}