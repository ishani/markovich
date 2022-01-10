

local initialDir = os.getcwd()
function GetInitialDir()
    return initialDir
end

function SrcRoot()
    return initialDir .. "/../"
end


-- ------------------------------------------------------------------------------
function SetDefaultBuildConfiguration()

    buildoptions { "/bigobj" }

    filter "configurations:Debug"
        defines   { "DEBUG" }
        symbols   "On"

    filter "configurations:Release"
        defines   { "NDEBUG" }
        flags     { "LinkTimeOptimization" }
        optimize  "Full"

    filter "configurations:Release-AVX2"
        defines   { "NDEBUG" }
        flags     { "LinkTimeOptimization" }
        optimize  "Full"
        vectorextensions "AVX2"

    filter {}

end

-- ------------------------------------------------------------------------------
function SetDefaultOutputDirectories(subgrp)

    targetdir   ( "$(SolutionDir)_artefact/bin_" .. subgrp .. "/$(Configuration)/%{cfg.platform}" )
    objdir      ( "!$(SolutionDir)_artefact/obj_" .. subgrp .. "/%{cfg.shortname}/$(ProjectName)/" )
    debugdir    ( "$(OutDir)" )

end


-- ==============================================================================
workspace ("markovich_" .. _ACTION)

    configurations  { "Debug", "Release", "Release-AVX2" }
    platforms       { "x86_64" }
    architecture      "x64"

    location "_sln"

    filter "platforms:x86_64"
        system "windows"
        defines 
        {
           "WIN32",
           "_WINDOWS",
        }

        vectorextensions "AVX"

    filter {}


-- ------------------------------------------------------------------------------
function StandardAppSetup( appname )

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    SetDefaultBuildConfiguration()
    SetDefaultOutputDirectories(appname)

    targetdir   ( "$(SolutionDir)../../bin/" .. appname .. "/build_%{cfg.shortname}" )

    links
    {
        "shlwapi",
        "ws2_32",
        "opengl32",
        "winmm",
        "dxguid.lib",
        "version.lib",
        "setupapi.lib",
        "imm32.lib",
    }

end


-- ------------------------------------------------------------------------------
project "runtime"

    StandardAppSetup("runtime")
    targetname ("markovich")

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        SrcRoot(),
        SrcRoot() .. "pcg",
    }
    
    files 
    {
        SrcRoot() .. "*.cpp",
        SrcRoot() .. "*.h",
        SrcRoot() .. "*.inl",

        SrcRoot() .. "generated/**.inl",

        SrcRoot() .. "pcg/*.h",
        SrcRoot() .. "pcg/*.c",

        SrcRoot() .. "chaiscript/**.hpp",
    }

    pchsource "../pch.cpp"
    pchheader "pch.h"