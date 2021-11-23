#include "buffer.h"

Buffer::Buffer(int buff_size){
    total_size_ = buff_size;
    data_ = (char*)malloc(sizeof(char) * buff_size);
    read_index_ = 0;
    write_index_ = 0;
}

void Buffer::Free(){
    free(data_);
}

int Buffer::ReadableSize(){
    return write_index_ - read_index_;
}

int Buffer::WriteAbleSize(){
    return total_size_ - write_index_;
}

int Buffer::FrontSpareSize(){
    return read_index_;
}

void Buffer::Append(void* s, int size){
    if (s != nullptr){
        memcpy(data_ + write_index_, s, size);
        write_index_ += size;
    }
}

void Buffer::AppendString(const char* s){
    int size = strlen(s);
    Append((void*)s, size);
}

int Buffer::SocketRead(int fd){
    char additional_buffer[65535];
    struct iovec vec[2];
    int max_writable = WriteAbleSize();
    vec[0].iov_base = data_ + write_index_;
    vec[0].iov_len = max_writable;
    vec[1].iov_base = additional_buffer;
    vec[1].iov_len = sizeof(additional_buffer);
    int result = readv(fd, vec, 2);
    if (result < 0) {
        return -1;
    } else if (result <= max_writable) {
        write_index_ += result;
    } else {
        write_index_ = total_size_;
        Append(additional_buffer, result - max_writable);
    }
    return result;
}