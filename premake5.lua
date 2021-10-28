-- Solution configuration file.
workspace "Workspace"
    --system "Windows"
    architecture "x86_64"
    --flags { 
        --"MultiProcessorCompile" 
    --}
    
    configurations {
        "Debug",
        "Release"
    }

    -- Set the startup project.
    startproject "Application"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Subprojects.
include "Application"

	postbuildcommands {
        "{COPY} Irrlicht.dll %{wks.location}/Application/build/bin/" .. outputdir .. "/Application/",
		"{COPY} lua54.dll %{wks.location}/Application/build/bin/" .. outputdir .. "/Application/"
		}



-- Clean.
newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("Application/build/bin")

        print("Removing intermediate binaries")
        os.rmdir("Application/build/bin-int")

        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}