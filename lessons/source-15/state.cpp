// Состояние (State)

#include <iostream>
#include <memory>

class ICommandHandler;
using ICommandHandlerPtr =  std::unique_ptr<ICommandHandler>;

class Application {
    ICommandHandlerPtr m_handler;

public:
    Application();

    void set_current(ICommandHandlerPtr hPtr) {
        m_handler = std::move(hPtr);
    }

    void login();

    void do_it();

    void logout();
};

class ICommandHandler {
public:
    virtual void login(Application *) = 0;
    virtual void do_it(Application *) = 0;
    virtual void logout(Application *) = 0;
};

void Application::login() {
    m_handler->login(this);
}

void Application::do_it() {
    m_handler->do_it(this);
}

void Application::logout() {
    m_handler->logout(this);
}


class LogginedHandler : public ICommandHandler {
public:
    void login(Application *) override {
        std::cout << "already login" << std::endl;
    }
    void do_it(Application *) override {
        std::cout << "success" << std::endl;
    }
    void logout(Application *m) override;
};

class Anonymous : public ICommandHandler {
public:
    void login(Application *m) override {
        std::cout << "work as loggined" << std::endl;
        m->set_current(ICommandHandlerPtr{new LogginedHandler()});
    }
    void do_it(Application *) override {
        std::cout << "error" << std::endl;
    }
    void logout(Application *m) override {
        std::cout << "already logout" << std::endl;
        m->set_current(ICommandHandlerPtr{new LogginedHandler()});
    }
};

void LogginedHandler::logout(Application *m) {
    std::cout << "work as anonymous" << std::endl;
    m->set_current(ICommandHandlerPtr{new Anonymous()});
}

Application::Application() {
    m_handler = ICommandHandlerPtr{new Anonymous()};
    std::cout << std::endl;
}

int main(int, char *[]) {
    Application app;

    app.do_it();
    app.logout();
    app.login();
    app.do_it();
    app.login();
    app.logout();

    return 0;
}
