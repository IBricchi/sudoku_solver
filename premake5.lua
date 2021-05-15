workspace "sudoku_solver"
    configurations { "debug", "release" }
    platforms { "win64", "linux64"}

    defaultplatform "win64"

    filter "platforms:win64"
        system "windows"
        architecture "x86_64"

    filter "platforms:linux64"
        system "linux"
        architecture "x86_64"

outputdir = "%{cfg.buildcfg}/%{cfg.platform}"

include "vendor/GLFW/premake5.lua"
include "vendor/glad/premake5.lua"

project "sudoku_solver"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++latest"

    dependson "GLFW"
    dependson "glad"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/obj/" .. outputdir .. "/%{prj.name}")

    files { "%{wks.location}/src/**.h", "%{wks.location}/src/**.cpp" }
 
    includedirs {
        "%{wks.location}/vendor/GLFW/include/",
        "%{wks.location}/vendor/glad/include/",
        "%{wks.location}/vendor/spdlog/include/",
    }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    filter "platforms:win64"
        staticruntime "on"
        links {
            "OpenGL32.lib",
            "GLFW",
            "glad",
        }

    filter "configurations:debug"
       defines { "DEBUG" }
       symbols "On"
 
    filter "configurations:release"
       defines { "NDEBUG" }
       optimize "On"