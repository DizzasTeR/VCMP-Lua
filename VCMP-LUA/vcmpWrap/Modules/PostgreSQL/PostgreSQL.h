#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

// PostgreSQL C API (libpq)
#include <libpq-fe.h>

// Lua bridge library
#include <sol/sol.hpp>

/**
 * @struct PgAccount
 * @brief Holds connection credentials and server information.
 */
struct PgAccount {
    std::string host;
    std::string user;
    std::string password;
    std::string database;
    int port = 5432; // Default PostgreSQL port
};

/**
 * @class PgConnection
 * @brief Manages a single PostgreSQL connection and provides an interface for Lua.
 */
class PgConnection {
public:
    /**
     * @brief Registers the PgConnection class and its methods into the Lua state.
     * @param L Pointer to the sol::state (Lua environment).
     */
    static void Init(sol::state* L);

    PgConnection();
    ~PgConnection();

    /**
     * @brief Establishes a connection to the database using the provided credentials.
     * @param acc A PgAccount struct containing host, user, password, etc.
     * @return True if connection is successful, false otherwise.
     */
    bool connect(const PgAccount& acc);

    /**
     * @brief Safely closes the active PostgreSQL connection.
     */
    void disconnect();

    /**
     * @brief Attempts to reconnect using the last stored credentials.
     * @return True if reconnection succeeds.
     */
    bool reconnect();

    /**
     * @brief Executes a SQL command (INSERT, UPDATE, DELETE) that does not return rows.
     * @param sql The SQL statement string.
     * @param args Variable arguments passed from Lua to be used as parameters.
     * @return True if execution was successful.
     */
    bool execute(
        const std::string& sql,
        sol::variadic_args args
    );

    /**
     * @brief Executes a SQL query (SELECT) and returns the result set as a Lua table.
     * @param ts The current Lua state context.
     * @param sql The SQL query string.
     * @param args Variable arguments passed from Lua for parameterized queries.
     * @return A sol::table containing the rows and columns from the result set.
     */
    sol::table query(
        sol::this_state ts,
        const std::string& sql,
        sol::variadic_args args
    );

    /**
     * @brief Escapes a string to prevent SQL injection.
     * @param str The raw input string.
     * @return The sanitized/escaped string.
     */
    std::string escape(const std::string& str);

    /**
     * @brief Performs a real round-trip to the server to check if the connection is alive.
     * Useful for detecting "zombie" or dropped connections.
     * @return True if the server responds, false otherwise.
     */
    bool ping();

private:
    PGconn* conn = nullptr;  // Internal libpq connection handle
    PgAccount lastAccount;   // Stores credentials for automatic reconnection

    /**
     * @brief Internal helper to verify connection health before running commands.
     * Tries to reconnect once if the connection is lost.
     * @return True if the connection is active or successfully restored.
     */
    bool ensureConnected();
};