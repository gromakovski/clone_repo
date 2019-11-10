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

	std::string serialize() const {
		const std::string result = 
		"{"
		"\n    \"firstName\": \"" + m_firstName + 
		"\n    \"lastName\": \"" + m_lastName +
		"\n    \"age\": \"" + std::to_string(m_age) +
		"\n}\n";
		return result;
	}

	bool deserialize(const std::string& json) {
		// not very difficult
		return true;
	}

private:
	std::string m_firstName;
	std::string m_lastName;
	uint8_t m_age;
};


struct PersonStorage {
	explicit PersonStorage(const std::string& tableName) 
		: m_tableName{tableName}
		, m_lastId{0} {

	}

	bool persistToDB(const Person& person, sqlite3* dbHandle) {
		assert(dbHandle);

		const std::string createQuery = "CREATE TABLE IF NOT EXISTS " + m_tableName + "(id, person);";

		// CREATE TABLE IF NOT EXISTS tableName(id, person);

		if (!utils::executeQuery(dbHandle, createQuery)) {
			std::cout << "PersonStorage::persistToDB - creation failed!" << std::endl;
			return false;
		}

		const std::string insertQuery = 
			"INSERT INTO " + m_tableName + " VALUES('" + std::to_string(m_lastId++)
				+ "', '" + person.serialize()  + "');";

		// INSERT INTO tableName VALUES('1', '{    "firstName": "Vasia", "lastName": "Ivanov", "age": 42    }');

		if (!utils::executeQuery(dbHandle, insertQuery)) {
			std::cout << "PersonStorage::persistToDB - insertion failed!" << std::endl;
			return false;
		}

		return true;
	}

	const std::string& getTableName() const {
		return m_tableName;
	}

private:
	std::string m_tableName;
	std::size_t m_lastId;
};	


int main() {

	const char* dbName = "motivation2.sqlite";
	sqlite3* dbHandle = nullptr;
	if (sqlite3_open(dbName, &dbHandle)) {
		std::cout << "sqlite3_open failed! " << sqlite3_errmsg(dbHandle) << std::endl;
		return -1;
	}

	PersonStorage storage("persons");

	Person person1{
		"Vasia", "Ivanov", 42
	};

	Person person2{
		"Ivan", "Vasiliev", 24
	};

	storage.persistToDB(person1, dbHandle);
	storage.persistToDB(person2, dbHandle);

	// load from DB ??

	utils::printAll(dbHandle, storage.getTableName());

	return 0;
}