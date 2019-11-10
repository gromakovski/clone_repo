// Одиночка (Singleton)

#include <iostream>
#include <string>

class Logger
{
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void info(const std::string &message) {
        std::cerr << "\tinfo: " << message << std::endl;
    }

    void warn(const std::string &message) {
        std::cerr << "warning: " << message << std::endl;
    }
private:
    Logger() = default;

    Logger(const Logger& root) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&& root) = delete;
    Logger& operator=(Logger&&) = delete;    

    ~Logger() = default;
};


int main() {
    // Compile error 
    // error: 'constexpr Logger::Logger()' is private within this context
    // Logger localLogger;

    Logger::getInstance().info("started");
    Logger::getInstance().warn("program is empty");

    Logger& logger = Logger::getInstance();
    logger.info("more logs");
    logger.warn("warning!");

    // Compile error
    // error: 'Logger::~Logger()' is private within this context
    // (&logger)->~Logger();

    return 0;
}
