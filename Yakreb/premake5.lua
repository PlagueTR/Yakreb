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
        "src/Yakreb/Platform/Windows/**",
        "src/Yakreb/Platform/Linux/**"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs{
        "src",
        "vendor",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "glad",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        files {
            "src/Yakreb/Platform/Windows/**"
        }

        defines {

        }

        links {
            
        }

    filter "system:linux"
        pic "on"

        files {
            "src/Yakreb/Platform/Linux/**"
        }

        defines {

        }

        links {
            
        }

    filter "configurations:Debug"
        defines {"YGE_DEBUG", "_DEBUG"}
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines {"YGE_RELEASE", "NDEBUG"}
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines {"YGE_DIST", "NDEBUG"}
        runtime "Release"
        optimize "on"
