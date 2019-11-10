#include "utils.h"

#include <iostream>
#include <cassert>

void utils::printAll(sqlite3* dbHandle, const std::string& tableName) {
	assert(dbHandle);

	auto readCallback = [](void* context, int columns, char **data, char **names) -> int {
		if (!columns) {
			std::cout << "Empty result!" << std::endl;
			return 1;
		}

		if (!names) {
			std::cout << "No columns!" << std::endl;
			return 1;
		}

		assert(context);
		bool * firstRow = static_cast<bool*>(context);

		if (*firstRow) {
			for (int i=0; i<columns; ++i) {
				if (i != 0)
					std::cout << '\t';
				std::cout << names[i];
			}
			std::cout << std::endl;
			*firstRow = false;
		}

		if (!data) {
			std::cout << "No data!" << std::endl;
			return 1;
		}

		for (int i=0; i<columns; ++i) {
			if (i != 0)
				std::cout << '\t';
			std::cout << data[i];
		}
		std::cout << std::endl;

		return 0;
	};

	const std::string selectAllQuery = "SELECT * FROM " + tableName + ";";
	bool firstRow = true;
	char * errMsg = nullptr;
	if (sqlite3_exec(dbHandle, selectAllQuery.c_str(), /*callback*/readCallback, /*cb 1st argument*/&firstRow, &errMsg)) {
		std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return;
	}
	std::cout << "Successfully selected!" << std::endl;
}


bool utils::executeQuery(sqlite3* dbHandle, const std::string& query) {
	assert(dbHandle);

	char * errMsg = nullptr;
	if (sqlite3_exec(dbHandle, query.c_str(), /*callback*/nullptr, /*cb 1st argument*/nullptr, &errMsg)) {
		std::cout << "utils::executeQuery - failed!" << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}

	return true;
}