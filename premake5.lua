--[[
	INSTRUCTIONS TO BUILD & LINK ON LINUX (DEBIAN SPECIFICALLY)
	1) dpkg --add-architecture i386
	2) apt-get update
	3) apt-get install build-essential gcc-multilib rpm libstdc++6:i386 libgcc1:i386 zlib1g:i386 libncurses5:i386 libmariadbclient-dev libmariadbclient-dev:i386
	3.extra) If needed: apt install libmariadb libmariadb:i386
	4) Generate gmake files with premake: premake gmake
	5) make config=[release/release32]
--]]

workspace "VCMPLua"
	architecture "x86_64"
	startproject "LuaPlugin"

	configurations
	{
		"Debug32",
		"Debug",
		"Release32",
		"Release"
	}

	filter "configurations:*32"
		architecture "x86"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	flags { "MultiProcessorCompile"	}
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "VCMP-LUA/vendor/Lua"
include "VCMP-LUA/vendor/spdlog"
include "VCMP-LUA"
