#include "pch.h"
#include "PostgreSQL.h"

#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ============================================================
// JSON -> LUA
// ============================================================

static sol::object JsonToLua(sol::state_view lua, const json& j)
{
    if (j.is_null())
        return sol::make_object(lua, sol::lua_nil);

    if (j.is_boolean())
        return sol::make_object(lua, j.get<bool>());

    if (j.is_number_integer())
    {
        return sol::make_object(
            lua,
            static_cast<lua_Integer>(
                j.get<long long>()));
    }

    if (j.is_number_unsigned())
    {
        return sol::make_object(
            lua,
            static_cast<lua_Integer>(
                j.get<unsigned long long>()));
    }

    if (j.is_number_float())
        return sol::make_object(lua, j.get<double>());

    if (j.is_string())
    {
        return sol::make_object(
            lua,
            j.get<std::string>());
    }

    if (j.is_array())
    {
        sol::table tbl = lua.create_table();
        int index = 1;
        for (const auto& item : j)
            tbl[index++] = JsonToLua(lua, item);
        return sol::make_object(lua, tbl);
    }

    if (j.is_object())
    {
        sol::table tbl = lua.create_table();
        for (auto it = j.begin(); it != j.end(); ++it)
            tbl[it.key()] = JsonToLua(lua, it.value());
        return sol::make_object(lua, tbl);
    }

    return sol::make_object(lua, sol::lua_nil);
}

// ============================================================
// LUA -> JSON
// ============================================================

static bool IsLuaArray(const sol::table& tbl)
{
    lua_Integer expectedIndex = 1;
    for (const auto& kv : tbl)
    {
        sol::object key = kv.first;
        if (!key.is<lua_Integer>())
            return false;
        if (key.as<lua_Integer>() != expectedIndex)
            return false;
        expectedIndex++;
    }
    return true;
}

static json LuaToJson(const sol::object& obj)
{
    switch (obj.get_type())
    {
        case sol::type::nil:
            return nullptr;

        case sol::type::boolean:
            return obj.as<bool>();

        case sol::type::number:
        {
            double num = obj.as<double>();
            if (std::floor(num) == num)
                return static_cast<long long>(num);
            return num;
        }

        case sol::type::string:
            return obj.as<std::string>();

        case sol::type::table:
        {
            sol::table tbl = obj.as<sol::table>();

            if (IsLuaArray(tbl))
            {
                json arr = json::array();
                for (const auto& kv : tbl)
                    arr.push_back(LuaToJson(kv.second));
                return arr;
            }

            json object = json::object();
            for (const auto& kv : tbl)
            {
                std::string key;
                if (kv.first.is<std::string>())
                    key = kv.first.as<std::string>();
                else if (kv.first.is<lua_Integer>())
                    key = std::to_string(kv.first.as<lua_Integer>());
                else
                    continue;
                object[key] = LuaToJson(kv.second);
            }
            return object;
        }

        default:
            return nullptr;
    }
}

// ============================================================
// HELPERS: escape conninfo value
// ============================================================

static std::string EscapeConnValue(const std::string& val)
{
    std::string out;
    out.reserve(val.size() + 2);
    out += '\'';
    for (char c : val)
    {
        if (c == '\'' || c == '\\')
            out += '\\';
        out += c;
    }
    out += '\'';
    return out;
}

// ============================================================
// CONNECTION IMPLEMENTATION
// ============================================================

PgConnection::PgConnection()
    : conn(nullptr)
{
}

PgConnection::~PgConnection()
{
    disconnect();
}

bool PgConnection::connect(const PgAccount& acc)
{
    disconnect();

    lastAccount = acc;

    std::string conninfo =
        "host="     + EscapeConnValue(acc.host)     +
        " user="    + EscapeConnValue(acc.user)     +
        " password="+ EscapeConnValue(acc.password) +
        " dbname="  + EscapeConnValue(acc.database) +
        " port="    + std::to_string(acc.port);

    conn = PQconnectdb(conninfo.c_str());

    return (PQstatus(conn) == CONNECTION_OK);
}

void PgConnection::disconnect()
{
    if (conn)
    {
        PQfinish(conn);
        conn = nullptr;
    }
}

bool PgConnection::reconnect()
{
    return connect(lastAccount);
}

bool PgConnection::ping()
{
    if (!conn)
        return false;

    PGresult* res = PQexec(conn, "SELECT 1");
    if (!res)
        return false;

    bool ok = (PQresultStatus(res) == PGRES_TUPLES_OK);
    PQclear(res);
    return ok;
}

bool PgConnection::ensureConnected()
{
    if (ping())
        return true;

    return reconnect();
}

// ============================================================
// EXECUTE WITH PARAMS
// ============================================================

static PGresult* ExecuteWithParams(PGconn* conn, const std::string& sql, sol::variadic_args args)
{
    std::vector<std::string> holders;

    std::vector<bool> nullFlags;

    for (auto arg : args)
    {
        try
        {
            // NIL -> SQL NULL real
            if (arg.get_type() == sol::type::nil)
            {
                holders.push_back("");
                nullFlags.push_back(true);
            }
            // BOOLEAN
            else if (arg.is<bool>())
            {
                holders.push_back(arg.as<bool>() ? "true" : "false");
                nullFlags.push_back(false);
            }
            // INTEGER
            else if (arg.is<lua_Integer>())
            {
                holders.push_back(std::to_string(arg.as<lua_Integer>()));
                nullFlags.push_back(false);
            }
            // FLOAT
            else if (arg.is<double>())
            {
                holders.push_back(std::to_string(arg.as<double>()));
                nullFlags.push_back(false);
            }
            // STRING
            else if (arg.is<std::string>())
            {
                holders.push_back(arg.as<std::string>());
                nullFlags.push_back(false);
            }
            // TABLE -> JSON
            else if (arg.get_type() == sol::type::table)
            {
                json j = LuaToJson(sol::object(arg));
                holders.push_back(j.dump());
                nullFlags.push_back(false);
            }
            // FALLBACK
            else
            {
                holders.push_back(arg.as<std::string>());
                nullFlags.push_back(false);
            }
        }
        catch (...)
        {
            holders.push_back("");
            nullFlags.push_back(false);
        }
    }

    std::vector<const char*> values;
    values.reserve(holders.size());

    for (size_t i = 0; i < holders.size(); i++)
        values.push_back(nullFlags[i] ? nullptr : holders[i].c_str());

    return PQexecParams(
        conn,
        sql.c_str(),
        static_cast<int>(values.size()),
        nullptr,
        values.data(),
        nullptr,
        nullptr,
        0
    );
}

// ============================================================
// EXECUTE
// ============================================================

bool PgConnection::execute(const std::string& sql, sol::variadic_args args)
{

    if (!ensureConnected())
        return false;

    PGresult* res = ExecuteWithParams(conn, sql, args);

    if (!res)
        return false;

    ExecStatusType status = PQresultStatus(res);
    PQclear(res);

    return (
        status == PGRES_COMMAND_OK ||
        status == PGRES_TUPLES_OK
    );
}

// ============================================================
// QUERY
// ============================================================

sol::table PgConnection::query(sol::this_state ts, const std::string& sql, sol::variadic_args args)
{
    sol::state_view lua(ts);
    sol::table results = lua.create_table();

    if (!ensureConnected())
        return results;

    PGresult* res = ExecuteWithParams(conn, sql, args);

    if (!res)
        return results;

    if (PQresultStatus(res) == PGRES_TUPLES_OK)
    {
        int rows = PQntuples(res);
        int cols = PQnfields(res);

        for (int i = 0; i < rows; i++)
        {
            sol::table row = lua.create_table();

            for (int j = 0; j < cols; j++)
            {
                const char* colName = PQfname(res, j);

                if (PQgetisnull(res, i, j))
                {
                    row[colName] = sol::lua_nil;
                    continue;
                }

                Oid type = PQftype(res, j);
                const char* value = PQgetvalue(res, i, j);

                try
                {
                    switch (type)
                    {
                        // BOOLEAN
                        case 16:
                            row[colName] = (value[0] == 't');
                            break;

                        // INTEGERS (int8, int2, int4)
                        case 20:
                        case 21:
                        case 23:
                            row[colName] = static_cast<lua_Integer>(std::stoll(value));
                            break;

                        // FLOATS (float4, float8, numeric)
                        case 700:
                        case 701:
                        case 1700:
                            row[colName] = std::stod(value);
                            break;

                        // JSON / JSONB
                        case 114:
                        case 3802:
                        {
                            json parsed = json::parse(value);
                            row[colName] = JsonToLua(lua, parsed);
                            break;
                        }

                        // DEFAULT STRING
                        default:
                            row[colName] = std::string(value);
                            break;
                    }
                }
                catch (...)
                {
                    row[colName] = std::string(value);
                }
            }

            results.add(row);
        }
    }

    PQclear(res);
    return results;
}

// ============================================================
// ESCAPE
// ============================================================

std::string PgConnection::escape(const std::string& str)
{
    if (!conn)
        return str;

    char* escaped = PQescapeLiteral(
        conn,
        str.c_str(),
        str.length());

    if (escaped)
    {
        std::string result(escaped);
        PQfreemem(escaped);
        return result;
    }

    return str;
}

// ============================================================
// FACTORIES
// ============================================================

static PgAccount CreateAccount(
    std::string h,
    std::string u,
    std::string p,
    std::string d,
    sol::optional<int> port)
{
    PgAccount acc;
    acc.host     = h;
    acc.user     = u;
    acc.password = p;
    acc.database = d;
    acc.port     = port.value_or(5432);
    return acc;
}

static std::shared_ptr<PgConnection>
CreateConnection(PgAccount& acc)
{
    auto conn = std::make_shared<PgConnection>();
    if (!conn->connect(acc))
        return nullptr;
    return conn;
}

// ============================================================
// LUA MODULE INIT
// ============================================================

void PgConnection::Init(sol::state* L)
{
    L->new_usertype<PgAccount>(
        "PgAccount",
        sol::constructors<PgAccount()>(),
        "host",     &PgAccount::host,
        "user",     &PgAccount::user,
        "password", &PgAccount::password,
        "database", &PgAccount::database,
        "port",     &PgAccount::port);

    L->new_usertype<PgConnection>(
        "PgConnection",
        sol::constructors<PgConnection()>(),
        "connect",    &PgConnection::connect,
        "disconnect", &PgConnection::disconnect,
        "reconnect",  &PgConnection::reconnect,
        "execute",    &PgConnection::execute,
        "query",      &PgConnection::query,
        "escape",     &PgConnection::escape,
        "ping",       &PgConnection::ping);

    sol::table pgTable = L->create_named_table("PostgreSQL");
    pgTable["createAccount"]    = &CreateAccount;
    pgTable["createConnection"] = &CreateConnection;
}