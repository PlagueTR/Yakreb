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
        "%{wks.location}/Yakreb/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links {
        "Yakreb"
    }

    postbuildcommands {
        "{COPYDIR} \"../Resources/Sandbox/\"* \"../bin/"..outputdir.."/Sandbox/\""
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
            "GLFW",
            "glad",
            "ImGui",
            "X11",
            "Xrandr",
            "Xi",
            "Xinerama",
            "Xxf86vm",
            "Xcursor",
            "Xrender",
            "GL",
            "pthread"
        }

    filter "configurations:Debug"
        defines {"YGE_DEBUG", "_DEBUG"}
        runtime "Debug"
        optimize "Off"
        symbols "On"
    
    filter "configurations:Release"
        defines {"YGE_RELEASE", "NDEBUG"}
        runtime "Release"
        optimize "On"
        symbols "Default"

    filter "configurations:Dist"
        defines {"YGE_DIST", "NDEBUG"}
        runtime "Release"
        optimize "Speed"
        symbols "Off"
