workspace "Arc"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Arc"
	location "Arc"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++19"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		"ARC_PLATFORM_WINDOWS",
		"ARC_BUILD_DLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ARC_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
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
		cppdialect "C++19"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		"ARC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ARC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ARC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ARC_DIST"
		optimize "On"