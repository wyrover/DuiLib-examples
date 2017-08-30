BOOK_CODE_PATH = "E:/book-code"
THIRD_PARTY = "E:/book-code/3rdparty"
WORK_PATH = os.getcwd()
includeexternal (BOOK_CODE_PATH .. "/premake-vs-include.lua")




workspace(path.getname(os.realpath(".")))
    language "C++"
    location "build/%{_ACTION}/%{wks.name}"    
    if _ACTION == "vs2015" then
        toolset "v140_xp"
    elseif _ACTION == "vs2013" then
        toolset "v120_xp"
    end

    include (BOOK_CODE_PATH .. "/common.lua")     

    function create_duilib_project(name, dir)        
        project(name)          
        targetdir("bin/" .. name)
        kind "WindowedApp"               
        defines { "_WINDOWS", "UILIB_STATIC" }
        files
        {                                  
            dir .. "/%{prj.name}/**.h",
            dir .. "/%{prj.name}/**.cpp", 
            dir .. "/%{prj.name}/**.c", 
            dir .. "/%{prj.name}/**.rc" 
        }
        removefiles
        {               
        }
        includedirs
        {          
            "3rdparty/DuiLib",
            "3rd",               
        }    
        links
        {
            "comctl32.lib"
        }
        link_libs
        {
            "DuiLib.lib",
        }
        
                
        has_stdafx(name, dir)
    end

    group "duilib"
        project "DuiLib"            
            kind "StaticLib"            
            defines { "_WINDOWS", "UILIB_STATIC" }     
                      
            files
            {
                "3rdparty/DuiLib/**.h",
                "3rdparty/DuiLib/**.cpp",  
                "3rdparty/DuiLib/**.c"
            }             
            removefiles
            {
                 
            }
            includedirs
            {            
                "3rdparty/DuiLib"    
            }
            links
            {
                "oledlg.lib",
                "winmm.lib",
                "comctl32.lib",
                "Riched20.lib"                
            }
            pchsource "3rdparty/DuiLib/StdAfx.cpp" 
            pchheader "StdAfx.h"
              

            filter "files:3rdparty/DuiLib/Utils/*.c"
                flags { "NoPCH" }
            filter "files:3rdparty/DuiLib/Utils/unzip.cpp"
                flags { "NoPCH" }  


    
        project "DuiLib_Dll"            
            kind "SharedLib"       
            targetname "DuiLib"
            defines { "_WINDOWS", "UILIB_EXPORTS" }                           
            files
            {
                "3rdparty/DuiLib/**.h",
                "3rdparty/DuiLib/**.cpp",  
                "3rdparty/DuiLib/**.c"
            }             
            removefiles
            {
                 
            }
            includedirs
            {            
                "3rdparty/DuiLib"    
            }
            links
            {
                "oledlg.lib",
                "winmm.lib",
                "comctl32.lib",
                "Riched20.lib"                
            }
            pchsource "3rdparty/DuiLib/StdAfx.cpp" 
            pchheader "StdAfx.h"
              

            filter "files:3rdparty/DuiLib/Utils/*.c"
                flags { "NoPCH" }
            filter "files:3rdparty/DuiLib/Utils/unzip.cpp"
                flags { "NoPCH" }  
            

            
            
    

    group "basic-examples"       
        
        --create_duilib_project("demo01", "Demos/basic_demos")
        matches = os.matchdirs("src/basic_demos/*")
        for i = #matches, 1, -1 do           
            create_duilib_project(path.getname(matches[i]), "src/basic_demos")
        end
--        
--
--    group "demos"
--
--        project "duidemo"
--            location "build"
--            targetdir "bin/duidemo"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/duidemo/**.h",
--                "Demos/duidemo/**.cpp",
--                "Demos/duidemo/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            }
--            
--    
--        project "gamebox"
--            location "build"
--            targetdir "bin/gamebox"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/gamebox/**.h",
--                "Demos/gamebox/**.cpp",
--                "Demos/gamebox/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            } 
--    
--        project "xlgamebox"
--            location "build"
--            targetdir "bin/xlgamebox"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/xlgamebox/**.h",
--                "Demos/xlgamebox/**.cpp",
--                "Demos/xlgamebox/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            } 
--            
--        project "transwnd"
--            location "build"
--            targetdir "bin/transwnd"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/transwnd/**.h",
--                "Demos/transwnd/**.cpp",
--                "Demos/transwnd/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            }   
--
--        project "bdwallpaper"
--            location "build"
--            targetdir "bin/bdwallpaper"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/bdwallpaper/**.h",
--                "Demos/bdwallpaper/**.cpp",
--                "Demos/bdwallpaper/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            }   
--
--        project "animationWindow"
--            location "build"
--            targetdir "bin/animationWindow"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/animationWindow/**.h",
--                "Demos/animationWindow/**.cpp",
--                "Demos/animationWindow/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            pchsource "Demos/animationWindow/stdafx.cpp" 
--            pchheader "stdafx.h"
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            }   
--            
--
--        project "ADMonSetup"
--            location "build"
--            targetdir "bin/ADMonSetup"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/ADMonSetup/**.h",
--                "Demos/ADMonSetup/**.cpp",
--                "Demos/ADMonSetup/**.rc"
--            }
--            includedirs
--            {          
--                "DuiLib",
--                "3rd",               
--            }    
--            links
--            {
--                "comctl32.lib"
--            }
--            link_libs
--            {
--                "DuiLib-s.lib",
--            }
--            
--        project "TroyBrowser"
--            location "build"
--            targetdir "bin/TroyBrowser"
--            kind "WindowedApp"              
--            defines { "_WINDOWS", "UILIB_STATIC" }
--            files
--            {
--                "Demos/TroyBrowser/**.h",
--                "Demos/TroyBrowser/**.cpp",
--                "Demos/TroyBrowser/**.rc"
--            }
--            includedirs
--            {
--                "DuiLib"
--                        
--            }
--            links
--            { 
--                "DuiLib.lib",
--                "TroyControls.lib",
--                "comctl32.lib"
--            }
--            libdirs
--            {
--                "bin/lib",
--                "Demos/TroyBrowser/Lib"
--            }
--
--        create_duilib_project("HiDPITest", "Demos")