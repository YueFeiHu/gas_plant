#pragma once
#include <string>
#include "common.h"
class Buffer{
    public:
        Buffer(int buff_size = 65535);
        void Free();
        int ReadableSize();
        int WriteAbleSize();
        int FrontSpareSize();
        void AppendString(const char* s);
        void Append(void* s, int size);
        int SocketRead(int fd); 
    private:
        void make_room(int size);
    private:

        char* data_;
        int read_index_;
        int write_index_;
        int total_size_;
};