// Адаптер (Adapter)

#include <iostream>

// Example 1.
class mysql_client_native {
public:
    void mysql_connect() {
        std::cout << "mysql connect" << std::endl;
    }

    void mysql_execute() {
        std::cout << "mysql execute" << std::endl;
    }

    void mysql_close() {
        std::cout << "mysql close" << std::endl;
    }
};

class postgresql_client_native {
public:
    void postgresql_open() {
        std::cout << "postgresql open" << std::endl;
    }

    void postgresql_query() {
        std::cout << "postgresql query" << std::endl;
    }
};

class IDatabase {
public:
    virtual void connect() = 0;
    virtual void execute_query() = 0;
    virtual void close() = 0;
};

class MysqlDatabase : public IDatabase {

    mysql_client_native client;

    void connect() override {
        client.mysql_connect();
    }

    void execute_query() override {
        client.mysql_execute();
    }

    void close() override {
        client.mysql_close();
    }
};

class PostgresqlDatabase : public IDatabase {

    postgresql_client_native client;

    void connect() override {
        client.postgresql_open();
    }

    void execute_query() override {
        client.postgresql_query();
    }

    void close() override{
    }
};



// Example 2.
struct JSONService {
    bool handle(const std::string& json) {
        // do something very interesting
        std::cout << "Json handling...." << std::endl;
        return true;
    }
};

struct XmlService {
    bool handle(const std::string& xml) {
        const std::string json = xmlToJson(xml);
        return m_realService.handle(json);
    }
private:
    std::string xmlToJson(const std::string& xml) {
        // do convetion here
        std::cout << "Xml convertion" << std::endl;
        return {xml};
    }
    JSONService m_realService;
};

int main(int, char *[]) { 
    IDatabase *db = new PostgresqlDatabase{};

    db->connect();
    db->execute_query();
    db->close();

    XmlService service;
    service.handle(
        "xml string"
    );
}
