workspace "Arc"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	IncludeDir = {}
	IncludeDir["GLFW"] = "Arc/vendor/GLFW/include"
	IncludeDir["Glad"] = "Arc/vendor/Glad/include"

	include "Arc/vendor/GLFW"
	include "Arc/vendor/Glad"

project "Arc"
	location "Arc"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "arcpch.h"
	pchsource "Arc/source/arcpch.cpp"

	files
	{
		"Arc/source/**.h",
		"Arc/source/**.cpp"
	}

	includedirs
	{
		"Arc/vendor/spdlog/include",
		"Arc/source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS",
			"ARC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ARC_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Sandbox/source/**.h",
		"Sandbox/source/**.cpp"
	}

	includedirs
	{
		"Arc/vendor/spdlog/include",
		"Arc/source"
	}

	links 
	{
		"Arc"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		"ARC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ARC_DIST"
		buildoptions "/MD"
		optimize "On"