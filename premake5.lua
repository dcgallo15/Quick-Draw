workspace "Quick Draw"
    architecture"x86"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Quick Draw"
    location "Quick Draw" 
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin-int/" .. outputdir .."/%{prj.name}")

    files 
    { 
        "src/**.h",
        "src/**.cpp",
        "res/**.h", 
        "res/**.cpp",
        "include/**.h"

    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "E:/Coding Stuff/EXTRA_LIBS/C++/SDL2_TTF/include",
        "E:/Coding Stuff/EXTRA_LIBS/C++/SDL2_image/include",
        "E:/Coding Stuff/EXTRA_LIBS/C++/SDL2/include"
    }

    libdirs
    {
        "E:/Coding Stuff/EXTRA_LIBS/C++/SDL2_TTF/lib/x86",
        "E:/Coding Stuff/EXTRA_LIBS/C++/SDL2_image/lib/x86",
        "E:/Coding Stuff/EXTRA_LIBS/C++/SDL2/lib/x86"
    }

    links
    {
        "SDL2.lib",
        "SDL2main.lib",
        "SDL2_image.lib",
        "SDL2_ttf.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "RELEASE","_CRT_NO_WARNINGS" }
        optimize "On"