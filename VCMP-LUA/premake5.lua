project "LuaPlugin"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    pic "On"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/interm/" .. outputdir .. "/%{prj.name}")

    files
    {
        "pch.h",
        "pch.cpp",
        "Core.cpp",
        "include/**.h",
        "include/**.c",
        "vcmpWrap/**.h",
        "vcmpWrap/**.cpp",
        "modules/crypto/vcmpWrap/**.h",
        "modules/crypto/vcmpWrap/**.cpp",
    }

    includedirs
    {
        "./",
        "include",
        "vcmpWrap",
        "vendor", 
        "vendor/Lua",
        "vendor/sol",
        "vendor/spdlog/include",
        "vendor/asyncplusplus/include",
        "vendor/lanes/src",
        "modules/sqlite3/sqliteCpp/include",
        "modules/requests/cpr/include",
        "modules/postgresql/include"
    }

    defines { 
        "LIBASYNC_STATIC"
    }

    filter "system:windows"

        defines {
            "WIN32",
            "CURL_STATICLIB",
            "ZLIB_WINAPI",
            "WIN32_LEAN_AND_MEAN",
            "NOMINMAX"
        }

        systemversion "latest"

        linkoptions {
            "/FORCE:MULTIPLE",
            "/alternatename:__imp_rand=rand",
            "/alternatename:__imp__rmdir=_rmdir"
        }
        
        libdirs { 
            "modules/postgresql/lib/%{cfg.architecture}-windows-static",
            "modules/requests/cpr/lib/%{cfg.architecture}-windows-static",
            "modules/sqlite3/sqliteCpp/lib/%{cfg.architecture}-windows-static"
        }
        
        links { 
            "spdlog", "Lua", "asyncplusplus", "LuaLanes", "module-crypto",
            "module-cpr", "module-sqliteCpp",
            "pq", "pgcommon", "pgport",
            "libcrypto", "libssl",
            "Ws2_32", "Secur32", "Advapi32", "Crypt32", "Wldap32", "Shell32", "Normaliz", "Iphlpapi" 
        }

    filter { "system:windows", "configurations:Release*" }
        links { "zs" } 

    filter { "system:windows", "configurations:Debug*" }
        links { "zsd" }

    filter "system:linux"
        buildoptions { "-fpermissive" }
        links { "pq", "module-cpr", "module-sqliteCpp", "ssl", "crypto", "pthread", "dl", "m" }

    filter "configurations:Debug"
        defines {"_DEBUG"}
        symbols "on"

    filter "configurations:Release*"
        defines {"_RELEASE"}
        optimize "on"