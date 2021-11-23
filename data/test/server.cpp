#include "../lib/common.h"

size_t readn(int fd, void* buffer, size_t size){
    char* pos = (char*)buffer;
    int length = size;
    while(length > 0){
        int n = read(fd, pos, length);
        if (n < 0) {
            if (errno == EINTR){
                continue;
            }
            else{
                return -1;
            }
        }
        else if(n == 0){
            break;
        }
        length -= n;
        pos += n;
    }
    return size - length;
}

void read_data(int fd){
    char buffer[10];
    while(true){
        bzero(buffer, 10);
        int n = readn(fd, buffer, 10);
        if(n <= 0){
            return;
        }
        printf("%s\n", buffer);
        sleep(1);
    }
}

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error(-1, errno, "创建socket错误");
    }
    sockaddr_in sock;
    bzero(&sock, sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sin_port = htons(PORT);
    int ret = bind(sockfd, (struct sockaddr*)&sock, sizeof(sock));
    int on = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if (ret == -1){
        error(-1, errno, "bind错误");
    }
    ret = listen(sockfd, 10);
    if (ret == -1){
        error(-1, errno, "listen错误");
    }
    socklen_t sl = sizeof(sock);
    for(;;){
        int fd = accept(sockfd, (struct sockaddr*)&sock, &sl);
        read_data(fd);
        close(fd);
    }
}
