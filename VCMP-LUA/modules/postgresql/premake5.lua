project "PostgreSQL"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetname "libpq"
    targetextension ".lib"
    targetdir "../../bin/%{cfg.buildcfg}"
    objdir "../../bin/interm/%{cfg.buildcfg}/PostgreSQL"

    defines { "PG_USE_STATIC" }

    files {
        "src/**.cpp",
        "src/**.h",
        "*.cpp",
        "*.h"
    }

    includedirs {
        "include",
        "include/internal",
        "../../include"
    }

    filter "system:windows"
        libdirs { "modules/postgresql/lib/%{cfg.architecture}-windows-static" }
        links { "libpq" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter { "system:windows", "configurations:Release*" }
    local ok = pcall(function() linktimeoptimization "On" end)
    if not ok then
        flags { "LinkTimeOptimization" }
    end