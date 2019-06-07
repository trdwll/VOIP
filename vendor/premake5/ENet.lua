project "ENet-Static"
    location "../../Intermediate/ProjectFiles/"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
	targetdir ("../../Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("../../Intermediate/" .. outputdir .. "/%{prj.name}")

    files
	{
        "../ENet/*.c",
	}

	includedirs
	{
		"../ENet/include",
	}
    
	filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on" 


project "ENet"
    location "../../Intermediate/ProjectFiles/"
    kind "SharedLib"
    language "C"
    
	targetdir ("../../Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("../../Intermediate/" .. outputdir .. "/%{prj.name}")

	defines({"ENET_DLL=1" })

    files
	{
        "../%{prj.name}/*.c",
	}

	includedirs
	{
		"../%{prj.name}/include",
	}
    
	filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on" 