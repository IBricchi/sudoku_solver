project "glad"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/obj/" .. outputdir .. "/%{prj.name}")
	
	includedirs { "include/" }

    files{
        "src/glad.c",
    }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "On"

    filter "system:windows"
		systemversion "latest"
		staticruntime "On"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"