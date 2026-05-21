workspace "VCMPLua"
    architecture "x86_64"
    startproject "LuaPlugin"

    targetname "%{prj.name}"
    targetprefix ""
    targetsuffix "_x64"

    configurations { "Release32", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- Arquitetura 32-bit
    filter "configurations:*32"
        architecture "x86"
        targetsuffix "_x86"
        defines { "_x32" }

    -- Release (todas as plataformas)
    filter "configurations:Release*"
        runtime "Release"
        optimize "On"
        symbols "Off"

    -- Windows
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        defines {
            "CURL_STATICLIB",
            "ZLIB_WINAPI"
        }

    -- Windows + Release (LTO)
    filter { "system:windows", "configurations:Release*" }
    local ok = pcall(function() linktimeoptimization "On" end)
    if not ok then
        flags { "LinkTimeOptimization" }
    end

    -- MSVC
    filter "toolset:msc"
        buildoptions { "/MP" }

    -- Linux
    filter "system:linux"
        pic "On"

    -- Linux + Release (LTO via flags de compilador)
    filter { "system:linux", "configurations:Release*" }
        buildoptions { "-flto" }
        linkoptions  { "-flto" }

filter {}

-- Includes
include "VCMP-LUA/vendor/Lua"
include "VCMP-LUA/vendor/spdlog"
include "VCMP-LUA/vendor/asyncplusplus"
include "VCMP-LUA/vendor/lanes"
include "VCMP-LUA/modules/crypto"
include "VCMP-LUA/modules/sqlite3"
include "VCMP-LUA/modules/requests"
include "VCMP-LUA/modules/postgresql"

-- Core
include "VCMP-LUA"