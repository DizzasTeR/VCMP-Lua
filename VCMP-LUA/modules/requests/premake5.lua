project "module-cpr"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    pic "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/interm/" .. outputdir .. "/%{prj.name}")

    files
    {
        "cpr/include/**.h",
        "cpr/src/**.cpp",
    }

    includedirs
    {
        "cpr/include"
    }
    
    libdirs
    {
        "cpr/lib/%{cfg.architecture}-windows-static"
    }

    defines 
    { 
        "CURL_STATICLIB" 
    }

    filter "system:windows"
		links
		{
			"cpr",
			"libcurl",
			"mongoose",
			"libssl",
			"libcrypto",
			"ws2_32",
			"wldap32",
			"crypt32",
			"normaliz",
			"advapi32",
			"bcrypt"
		}

    filter "system:linux"
        links
        {
            "curl",
            "pthread",
            "ssl",
            "crypto"
        }

    filter {}