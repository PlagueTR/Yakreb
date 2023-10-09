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

        }

        defines {

        }

        links {
            
        }

    filter "system:linux"
        pic "on"

        files {

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
