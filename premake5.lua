dofile "Scripts/Premake/generate_version.lua"

include "Dependencies.lua"

workspace "Yakreb"
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

group "1) Dependencies"
    include "Yakreb/vendor/GLFW"
    include "Yakreb/vendor/glad"
    include "Yakreb/vendor/imgui"
group ""

group "2) Core"
    include "Yakreb"
group ""

group "3) Testing"
    include "Sandbox"
group ""
