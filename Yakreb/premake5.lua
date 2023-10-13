project "Yakreb"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "yakrebpch.h"
    pchsource "src/yakrebpch.cpp"

    files {
        "src/**.h",
        "src/**.cpp"
    }

    removefiles {
        "src/Platform/Windows/**",
        "src/Platform/Linux/**"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs{
        "src"
    }

    links {

    }

    filter "system:windows"
        systemversion "latest"

        files {
            "src/Platform/Windows/**"
        }

        defines {

        }

        links {
            
        }

    filter "system:linux"
        pic "on"

        files {
            "src/Platform/Linux/**"
        }

        defines {

        }

        links {
            
        }

    filter "configurations:Debug"
        defines "YGE_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "YGE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "YGE_DIST"
        runtime "Release"
        optimize "on"
