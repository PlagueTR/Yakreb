dofile "Scripts/Premake/generate_version.lua"

include "Dependencies.lua"

workspace "YakrebGameEngine"
    architecture "x86_64"
    configurations{
        "Debug",
        "Release",
        "Dist"
    }

startproject "Sandbox"

    flags{
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "Yakreb/vendor/GLFW"
    include "Yakreb/vendor/glad"
    include "Yakreb/vendor/imgui"
group ""

group "YakrebCore"
    include "Yakreb"
group ""

group "Testing"
    include "Sandbox"
group ""
