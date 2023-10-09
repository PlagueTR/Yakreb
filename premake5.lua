require "vendor/premake/ext/codeblocks"

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
group ""

group "YakrebCore"
    include "Yakreb"
group ""

group "Testing"
    include "Sandbox"
group ""
