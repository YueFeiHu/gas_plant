#pragma once

#include <functional>

#define EVENT_TIMEOUT    0x01
/** Wait for a socket or FD to become readable */
#define EVENT_READ        0x02
/** Wait for a socket or FD to become writeable */
#define EVENT_WRITE    0x04
/** Wait for a POSIX signal to be raised*/
#define EVENT_SIGNAL    0x08


class Channel{
    public:
        Channel(int fd, int events, std::function<int(void*)> read_cb, std::function<int(void*)> write_cb, void* data);
    private:
        int fd_;
        int events_; // 事件类型
        std::function<int(void*)> read_cb_; 
        std::function<int(void*)> write_cb_; 
        void* data_;
};