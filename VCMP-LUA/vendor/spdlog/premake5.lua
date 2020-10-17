project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	pic "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/interm/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"include/spdlog/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/VCMP-LUA/vendor/spdlog/include"
	}
	
    filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"