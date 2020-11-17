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
	IncludeDir["glm"] = "Arc/vendor/glm"
	IncludeDir["stb_image"] = "Arc/vendor/stb_image"

	group "Dependencies"
		include "Arc/vendor/GLFW"
		include "Arc/vendor/Glad"
		include "Arc/vendor/ImGui"
	group ""

project "Arc"
	location "Arc"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "arcpch.h"
	pchsource "Arc/source/arcpch.cpp"

	files
	{
		"Arc/source/**.h",
		"Arc/source/**.cpp",
		"Arc/vendor/stb_image/**.h",
		"Arc/vendor/stb_image/**.cpp",
		"Arc/vendor/glm/glm/**.hpp",
		"Arc/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Arc/vendor/spdlog/include",
		"Arc/source",
		"Arc/vendor/imgui/backends",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS",
			"ARC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ARC_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Arc/source",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{
		"Arc"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ARC_DIST"
		runtime "Release"
		optimize "on"