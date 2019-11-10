// This example will not compile

#include "sqlite/sqlite3.h"

#include <iostream>
#include <string>
#include <vector>

struct Person {
	Person(const std::string &firstName, const std::string &lastName, uint8_t age);

    const std::string& getFirstName() const;

    const std::string& getLastName() const;

    /*const*/ uint8_t getAge() const;
private:
	std::string m_firstName;
	std::string m_lastName;
	uint8_t m_age;
};

struct AbstractQuery {
    
};

struct SQLiteQuery : public AbstractQuery {

};

struct PersonRepositoryInterface {
    virtual bool insert(const Person& person) = 0;
    
    virtual bool update(const Person& Person) = 0;

    virtual bool remove(const Person& person) = 0;

    virtual std::vector<Person> query(AbstractQuery* query) = 0;
};

struct PersonDAOSQLite : public PersonRepositoryInterface {
public:
    PersonDAOSQLite(const std::string& tableName, sqlite3* dbHandle);

    bool insert(const Person& person) override;
    
    bool update(const Person& Person) override;

    virtual std::vector<Person> query(SQLiteQuery* query) = 0;
private:
    std::string m_tableName;
    sqlite3* m_dbHandle;
};


int main() {

    std::cout << "Sorry, this code is not compile..." << std::endl;

    return 0;
}