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


-- include "ENet"


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
		-- "ENet-Static",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VOIP_PLATFORM_WINDOWS",
		}

		links 
		{
			"Ws2_32.lib",
			"Mswsock.lib",
			"AdvApi32.lib"
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
		"../../%{prj.name}/Source/**.cpp",
		-- "../cef/include/**.h",
		-- "../cef/tests/**.h"
	}

	includedirs
	{
		"../../VOIP/Source",
		"../spdlog/include",
		"../../Source",
		-- "../cef/include",
		-- "../cef/tests",
	}

	links
	{
		"VOIP",
		-- "../cef-win-build/Release/cef_sandbox.lib",
		-- "../cef-win-build/Release/libcef.lib",
		-- "../cef-win-build/Release/libcef_dll_wrapper.lib",
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
		"../../VOIP/Source",
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