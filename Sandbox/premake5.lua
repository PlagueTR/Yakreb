project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "%{wks.location}/Yakreb/src"
    }

    links {
        "Yakreb"
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
