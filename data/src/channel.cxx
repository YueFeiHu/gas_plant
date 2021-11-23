#include "channel.h"

Channel::Channel(int fd, int events, std::function<int(void*)> read_cb, 
                std::function<int(void*)> write_cb, void* data){
    fd_ = fd;
    events_ = events;
    read_cb_ = read_cb;
    write_cb_ = write_cb;
    data_ = data;
}
