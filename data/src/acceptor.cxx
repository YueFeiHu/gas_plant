#include "acceptor.h"
#include "common.h"

Acceptor::Acceptor(int port){
    this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    this->port = port;
    if (this->listen_fd <= 0){
        error(1, errno, "create socket error");
    }
    sockaddr_in sock;
    bzero(&sock, sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sin_port = htons(port);

    int ret1 = bind(this->listen_fd, (sockaddr*)&sock, sizeof(sock));
    if(ret1 < 0){
        error(1, errno, "bind error");
    }

    int on = 1;
    setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    int ret2 = listen(this->listen_fd, 10);
    if (ret2 < 0) {
        error(1, errno, "listen error");
    }
}

int Acceptor::get_listen_fd(){
    return listen_fd;
}
