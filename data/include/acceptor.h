
class Acceptor{
    public:
        Acceptor(int port = 12345);
        int get_listen_fd();
    private:
        int port;
        int listen_fd;
};