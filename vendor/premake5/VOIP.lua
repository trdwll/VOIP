workspace "VOIP"
	location "../../"
	architecture "x64"
	startproject "VOIP-Client"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to solution directory
IncludeDir = {}


project "VOIP"
	location "../../Intermediate/ProjectFiles/"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../../Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("../../Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "voippch.h"
	pchsource "../../%{prj.name}/Source/voippch.cpp"

	files
	{
		"../../%{prj.name}/Source/**.h",
		"../../%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"../../%{prj.name}/Source",
		"../spdlog/include",
	}

	links 
	{
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VOIP_PLATFORM_WINDOWS",
		}
	
	filter "system:linux"
		systemversion "latest"
		pic "on"

		defines 
		{
			"VOIP_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "VOIP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VOIP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "VOIP_DIST"
		runtime "Release"
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MDd"

	filter { "system:windows", "configurations:Release" }
        buildoptions "/MD"
		
	filter { "system:windows", "configurations:Distribution" }
        buildoptions "/MD"


-- VOIP-Client

project "VOIP-Client"
	location "../../Intermediate/ProjectFiles/"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("../../Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("../../Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../../%{prj.name}/Source/**.h",
		"../../%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"../",
		"../spdlog/include",
		"../../Source",
	}

	links
	{
		"VOIP",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VOIP_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		systemversion "latest"
		pic "on"

		defines 
		{
			"VOIP_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "VOIP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VOIP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "VOIP_DIST"
		runtime "Release"
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MDd"

	filter { "system:windows", "configurations:Release" }
        buildoptions "/MD"
		
	filter { "system:windows", "configurations:Distribution" }
		buildoptions "/MD"
		

-- VOIP-Server

project "VOIP-Server"
	location "../../Intermediate/ProjectFiles/"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("../../Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("../../Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../../%{prj.name}/Source/**.h",
		"../../%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"../",
		"../spdlog/include",
		"../../Source",
	}

	links
	{
		"VOIP",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VOIP_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		systemversion "latest"
		pic "on"

		defines 
		{
			"VOIP_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "VOIP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VOIP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "VOIP_DIST"
		runtime "Release"
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MDd"

	filter { "system:windows", "configurations:Release" }
        buildoptions "/MD"
		
	filter { "system:windows", "configurations:Distribution" }
        buildoptions "/MD"