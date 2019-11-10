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

struct PersonDAOInterface {
    virtual bool insert(const Person& person) = 0;
    
    virtual bool update(const Person& Person) = 0;

    virtual bool remove(const Person& person) = 0;

    virtual Person find(const std::string& firstName) = 0;
#pragma region AfterAWhile
    virtual Person findByLastName(const std::string& lastName) = 0;

    virtual std::vector<Person> findAllByAge(uint8_t age) = 0;
#pragma endregion
};

struct PersonDAOSQLite : public PersonDAOInterface {
public:
    PersonDAOSQLite(const std::string& tableName, sqlite3* dbHandle);

    bool insert(const Person& person) override;
    
    bool update(const Person& person) override;

    bool remove(const Person& person) override;

    Person find(const std::string& firstName) override;
#pragma region AfterAWhile
    Person findByLastName(const std::string& lastName) override;

    std::vector<Person> findAllByAge(uint8_t age) override;
#pragma endregion
private:
    std::string m_tableName;
    sqlite3* m_dbHandle;
};


int main() {

    std::cout << "Sorry, this code is not compile..." << std::endl;

    return 0;
}