// Прототип (Prototype)

#include <iostream>
#include <map>

class Connection
{
public:
    virtual ~Connection() = 0 {};

    virtual void connection() = 0;

    virtual Connection *clone() = 0;
};

class TcpConnector : public Connection
{
public:
    void connection() override
    {
        std::cout << "tcp connection" << std::endl;
    }
public:
    TcpConnector *clone() override
    {
        return new TcpConnector{};
    }
};

class UdpConnector : public Connection
{
public:
    void connection() override
    {
        std::cout << "udp connection" << std::endl;
    }
public:
    UdpConnector *clone() override
    {
        return new UdpConnector{};
    }
};

int main()
{
    Connection *c = new TcpConnector{};

    //

    std::cout << "primary" << std::endl;
    c->connection();

    auto mirror = c->clone();
    std::cout << "mirror" << std::endl;
    mirror->connection();

    return 0;
}
