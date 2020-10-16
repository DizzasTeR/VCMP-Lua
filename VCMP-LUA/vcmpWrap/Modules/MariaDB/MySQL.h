#pragma once
#include "pch.h"

#include "MySQLAccount.h"
#include "MySQLConnection.h"

class MySQL {
public:
	static void Init(sol::state* Lua);
	static inline void LogError() {
		mariadb::last_error error;
		if (error.error_no() == 0) return;
		spdlog::error("MySQL Error: [{}] {}", error.error_no(), error.error());
	}

	/*** METHODS ***/
	static MySQLAccount* createAccount(const std::string& host, const std::string& user, const std::string& password, const std::string& database, mariadb::u32 port = 3306U, const std::string& unix_socket = "");
	static MySQLConnection* createConnection(MySQLAccount* account);
};