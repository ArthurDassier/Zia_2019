#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket)
            : _socket(std::move(socket))
        {
        }

        void start()
        {
            do_read();
        }

    private:
        void do_read()
        {
            auto self(shared_from_this());
            _socket.async_read_some(boost::asio::buffer(_data, max_length),
                [this, self](boost::system::error_code ec, std::size_t length)
                {
                if (!ec)
                {
                    do_write(length);
                    std::cout << "data :" << _data;
                } 
                else
                {
                    std::cout << "deco de : " << _socket.remote_endpoint().address().to_string() << std::endl;
                }
                });
        }

        void do_write(std::size_t length)
        {
            auto self(shared_from_this());
            boost::asio::async_write(_socket, boost::asio::buffer(_data, length),
                [this, self](boost::system::error_code ec, std::size_t /*length*/)
                {
                if (!ec)
                {
                    do_read();
                }
                });
        }

        tcp::socket _socket;
        enum { max_length = 1024 };
        char _data[max_length];
};

class tcp_server
{
    public:
        tcp_server(boost::asio::io_service& io_service, short port)
            : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
            _socket(io_service)
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            _acceptor.async_accept(_socket,
                [this](boost::system::error_code ec)
                {
                if (!ec)
                {
                    std::string s = _socket.remote_endpoint().address().to_string(); //a faire avant sinon crash -> perd la socket
                    std::cout << "new session created, client: " << s << std::endl;
                    std::make_shared<session>(std::move(_socket))->start();
                }
                do_accept();
                });
        }

        tcp::acceptor _acceptor;
        tcp::socket _socket;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>" << std::endl;
            return 84;
        }
        boost::asio::io_service io_service;
        tcp_server s(io_service, std::atoi(argv[1]));

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}