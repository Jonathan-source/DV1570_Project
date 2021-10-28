project "Application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
   -- disablewarnings{"26812"}
    --linkoptions { "-IGNORE:4075", "-IGNORE:4098", "-IGNORE:4099"}
    targetdir("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir("build/bin-int/" .. outputdir .. "/%{prj.name}")


    -- Define the location(s) of files.
    files {
        "src/**.h",
		"src/**.cpp",
    }


    -- Define any includes of folder(s).
    -- Useful to remove any "../folder/file.h" in code.
    includedirs {
        "src",
		"../lib/x64/",
		"../include/",
		"../Lua542/include/",
    }

   -- vpaths {
      --  ["src/Application"] = { "**Application.*" },
    --        ["src/Game/Scenes"] = { "**DemoScene.*" }
   -- }

    
	links {
      --"Irrlicht",
		--"lua54.dll",
		}

	libdirs {
			"../lib/x64/",
		}

    --filter {"system:windows"}
        --defines {
         --   "WIN32",
         --   "_CRT_SECURE_NO_WARNINGS"
       -- }
		
	--postbuildcommands {
			--"{COPY} Irrlicht.dll %{wks.location}/Application/build/bin/" .. outputdir .. "/Application/"
			--os.copyfile("../Irrlicht.dll" , "../Application/build/bin/Debug-windows-x86_64/Application/"),
			--os.copyfile("../lua54.dll" , "../Application/build/bin/Debug-windows-x86_64/Application/"),
		--}