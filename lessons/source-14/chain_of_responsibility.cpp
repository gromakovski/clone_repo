// Цепочка ответственности (Chain of responsibilily)

#include <iostream>
#include <string>

class Handler {
public:
    Handler() 
        : m_next(nullptr) {

    }

    void add(Handler *n) {
        if (m_next)
            m_next->add(n);
        else
            m_next = n;
    }

    virtual void exec(const std::string &line) {
        if (m_next) {
            m_next->exec(line);
        }
    }
private:
    Handler* m_next;
};


class DropHandler : public Handler {
public:
    void exec(const std::string &line) override {
        if (line.find("DROP") == 0) {
            std::cout << "DropHandler accept " << line << std::endl;
        } else {
            std::cout << "DropHandler pass" << std::endl;
            Handler::exec(line);
        }
    }
};

class SelectHandler : public Handler {
public:
    void exec(const std::string &line) override {
        if (line.find("SELECT") == 0) {
            std::cout << "SelectHandler accept " << line << std::endl;
        } else {
            std::cout << "SelectHandler pass" << std::endl;
            Handler::exec(line);
        }
    }
};

class CreateHandler: public Handler {
public:
    void exec(const std::string &line) override {
        if (line.find("CREATE") == 0) {
            std::cout << "CreateHandler accept " << line << std::endl;
        } else {
            std::cout << "CreateHandler pass" << std::endl;
            Handler::exec(line);
        }
    }
};

int main(int, char *[])
{
    DropHandler handler;

    SelectHandler select;
    CreateHandler create;

    handler.add(&select);
    handler.add(&create);

    handler.exec("CREATE table");
    handler.exec("SELECT * FROM table");
    handler.exec("DROP table");

    return 0;
}
