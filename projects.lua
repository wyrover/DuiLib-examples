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
            "3rdparty",
            "3rd", 
            "%{THIRD_PARTY}",
            "%{THIRD_PARTY}/wtl"
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
        project "cactus_lite"            
            kind "SharedLib"            
            defines { "_WINDOWS", "_USRDLL", "DLL_EXPORTS", "CACTUS_DLL", "CACTUS_EXPORTS" }               
            buildoptions { "/EHsc", "/Zm200" }   
            flags { "NoManifest" }
            files
            {
                "%{THIRD_PARTY}/cactus/cactus.h",
                "%{THIRD_PARTY}/cactus/cactus_types.h",
                "%{THIRD_PARTY}/cactus/cactus_thread_helper.h",
                "%{THIRD_PARTY}/cactus/cactus_thread_helper.cpp",
                --"%{THIRD_PARTY}/cactus/cactus_file.cpp",  
                
                "%{BOOK_CODE_PATH}/include/buildcfg/vs2015/dll_version.rc",
                "%{BOOK_CODE_PATH}/include/buildcfg/vs2015/versionno.rc2",                
                "%{BOOK_CODE_PATH}/include/buildcfg/vs2015/buildcfg.h"
            }             
            removefiles
            {
                
            }
            includedirs
            {            
                "%{THIRD_PARTY}",
                "3rdparty"    
            }                

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
                "3rdparty/DuiLib",
                "%{THIRD_PARTY}",
                "3rdparty"
            }
            links
            {
                "oledlg.lib",
                "winmm.lib",
                "comctl32.lib",
                "Riched20.lib",
                "cactus_lite.lib"
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
                "3rdparty/DuiLib",
                "%{THIRD_PARTY}",
                "3rdparty"
            }
            links
            {
                "oledlg.lib",
                "winmm.lib",
                "comctl32.lib",
                "Riched20.lib",
                "cactus_lite.lib"
              
            }
            pchsource "3rdparty/DuiLib/StdAfx.cpp" 
            pchheader "StdAfx.h"
              

            filter "files:3rdparty/DuiLib/Utils/*.c"
                flags { "NoPCH" }
            filter "files:3rdparty/DuiLib/Utils/unzip.cpp"
                flags { "NoPCH" }  
            
    
    group "UiLib"
        
        project "UiLib_Dll"            
            kind "SharedLib"       
            targetname "UiLib"
            defines { "_WINDOWS", "UILIB_EXPORTS" }                           
            files
            {
                "3rdparty/UiLib/**.h",
                "3rdparty/UiLib/**.cpp",  
                "3rdparty/UiLib/**.c"
            }             
            removefiles
            {
                 
            }
            includedirs
            {            
                "3rdparty/UiLib",                
            }
            links
            {
                "oledlg.lib",
                "winmm.lib",
                "comctl32.lib",
                "Riched20.lib",
                
              
            }
            pchsource "3rdparty/UiLib/StdAfx.cpp" 
            pchheader "StdAfx.h"
              

            filter "files:3rdparty/UiLib/Utils/*.c"
                flags { "NoPCH" }
            filter "files:3rdparty/UiLib/Utils/XUnzip.cpp"
                flags { "NoPCH" }  
            
    
        project "cloneKuGou"          
            targetdir "bin/cloneKuGou"
            kind "WindowedApp"               
            defines { "_WINDOWS", "UILIB_STATIC" }
            files
            {                                  
                "src/cloneKuGou/**.h",
                "src/cloneKuGou/**.cpp",
                "src/cloneKuGou/**.c",
                "src/cloneKuGou/**.rc",
                
            }
            removefiles
            {               
            }
            includedirs
            {          
                "3rdparty/UiLib",
                "3rdparty",               
                "%{THIRD_PARTY}/wtl"
            }    
            links
            {
                "comctl32.lib"
            }
            link_libs
            {
                "UiLib.lib",
            }

    group "basic-examples"       
        
        --create_duilib_project("demo01", "Demos/basic_demos")
        matches = os.matchdirs("src/basic_demos/*")
        for i = #matches, 1, -1 do           
            create_duilib_project(path.getname(matches[i]), "src/basic_demos")
        end
        

    group "demos"
        create_duilib_project("duidemo2", "src")
        create_duilib_project("duidemo", "src")
        create_duilib_project("gamebox", "src")
        create_duilib_project("xlgamebox", "src")
        create_duilib_project("transwnd", "src")
        create_duilib_project("bdwallpaper", "src")
        create_duilib_project("animationWindow", "src")
        create_duilib_project("ADMonSetup", "src")
        create_duilib_project("TroyBrowser", "src")
            links
            {                 
                "TroyControls.lib",                
            }
            libdirs
            {
                
                "src/TroyBrowser/Lib"
            }

        create_duilib_project("HiDPITest", "src")
        create_duilib_project("menu_win_shadow_demo", "src")
        create_duilib_project("transwnd2", "src")
        create_duilib_project("360SafeDemo", "src")
        create_duilib_project("WeChatDemo", "src")
        create_duilib_project("CNTVDemo", "src")
        create_duilib_project("TestApp1", "src")
        create_duilib_project("ListDemo", "src")
        create_duilib_project("FlashDemo", "src")
        