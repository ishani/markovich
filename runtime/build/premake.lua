

local initialDir = os.getcwd()
function GetInitialDir()
    return initialDir
end

function SrcRoot()
    return initialDir .. "/../"
end


-- ------------------------------------------------------------------------------
function SetDefaultBuildConfiguration()

    filter "system:Windows"
    buildoptions { "/bigobj" }
    filter {}

    filter "configurations:Debug"
        defines   { "DEBUG" }
        symbols   "On"

    filter "configurations:Release"
        defines   { "NDEBUG" }
        flags     { "LinkTimeOptimization" }
        optimize  "Full"

    -- custom config for the 'miniature' demo that doesn't use chai
    filter "configurations:Mini"
        defines   { "DEBUG", "MK_MINI_DEMO" }
        symbols   "On"

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

    configurations  { "Debug", "Release", "Mini" }
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

    filter "system:macosx"
        platforms       { "universal" }
        architecture      "universal"
        system            "macosx"
        systemversion     "11.0"
        
        buildoptions
        {
            "-Wall"
        }
    filter {}
    


-- ------------------------------------------------------------------------------
function StandardAppSetup( appname )

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    SetDefaultBuildConfiguration()
    SetDefaultOutputDirectories(appname)

    targetdir   ( "$(SolutionDir)../../bin/" .. appname .. "/build_%{cfg.shortname}" )

    filter "system:Windows"
    links
    {
        "shlwapi",
        "version.lib",
        "setupapi.lib",
        "imm32.lib",
    }
    filter {}

    filter "system:macosx"
    links 
    {
    }
    filter {}

end


-- ------------------------------------------------------------------------------
project "runtime"

    StandardAppSetup("runtime")
    targetname ("markovich")

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    externalincludedirs
    {
        SrcRoot()
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

    -- pch header reference rules different on win vs osx

    filter "system:Windows"
    pchheader "pch.h"
    filter {}

    filter "system:macosx"
    pchheader ( SrcRoot() .. "pch.h" )
    filter {}