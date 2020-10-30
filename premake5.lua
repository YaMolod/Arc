workspace "Arc"
	architecture "x64"
	startproject "Sandbox"
	
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
	IncludeDir["ImGui"] = "Arc/vendor/ImGui"

	group "Dependencies"
		include "Arc/vendor/GLFW"
		include "Arc/vendor/Glad"
		include "Arc/vendor/imgui"
	group ""

project "Arc"
	location "Arc"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS",
			"ARC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ARC_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "latest"

		defines
		{
		"ARC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ARC_DIST"
		runtime "Release"
		optimize "On"