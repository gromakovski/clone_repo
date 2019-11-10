#include "sqlite/sqlite3.h"
#include "utils.h"

#include <iostream>

#include <cassert>

struct Person {
	Person(
		const std::string &firstName,
		const std::string &lastName,
		uint8_t age
	) :
	m_firstName(firstName)
	, m_lastName(lastName)
	, m_age(age) {

	}

	bool persistToDB(sqlite3* dbHandle) {
		const std::string createQuery = "CREATE TABLE IF NOT EXISTS " + getTableName() + "(firstName, lastName, age);";

		// CREATE TABLE IF NOT EXISTS persons(firstName, lastName, age);

		if (!utils::executeQuery(dbHandle, createQuery)) {
			std::cout << "Person::persistToDB - creation failed!" << std::endl;
			return false;
		}

		const std::string insertQuery = "INSERT INTO " + getTableName() + " VALUES('" + 
			m_firstName + "', '" +
			m_lastName + "', " +
			std::to_string(m_age) + ");";

		// INSERT INTO persons VALUES('Vasia', 'Ivanov', 42);

		if (!utils::executeQuery(dbHandle, insertQuery)) {
			std::cout << "Person::persistToDB - insertion failed!" << std::endl;
			return false;
		}

		return true;
	}

	static const std::string& getTableName() {
		const static std::string name = "persons";
		return name;
	}

private:
	std::string m_firstName;
	std::string m_lastName;
	uint8_t m_age;
};



int main() {

	const char* dbName = "motivation1.sqlite";
	sqlite3* dbHandle = nullptr;
	if (sqlite3_open(dbName, &dbHandle)) {
		std::cout << "sqlite3_open failed! " << sqlite3_errmsg(dbHandle) << std::endl;
		return -1;
	}

	Person person{
		"Vasia", "Ivanov", 42
	};
	person.persistToDB(dbHandle);

	Person person2{
		"Ivan", "Vasiliev", 24
	};
	person2.persistToDB(dbHandle);

	// load from DB ??

	utils::printAll(dbHandle, Person::getTableName());

	return 0;
}