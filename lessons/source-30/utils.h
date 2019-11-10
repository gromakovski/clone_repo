#pragma once

#include "sqlite/sqlite3.h"

#include <string>

namespace utils {

	void printAll(sqlite3* dbHandle, const std::string& tableName);

	bool executeQuery(sqlite3* dbHandle, const std::string& query);

} // utils