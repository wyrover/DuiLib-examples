// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
//#include "drivergenius/utils/sdk.h"

// 如果必须将位于下面指定平台之前的平台作为目标，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef WINVER                      // 允许使用特定于 Windows XP 或更高版本的功能。
   #define WINVER          0x0600        // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT                // 允许使用特定于 Windows XP 或更高版本的功能。
    #define _WIN32_WINNT    0x0600    // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINDOWS              // 允许使用特定于 Windows 98 或更高版本的功能。
    #define _WIN32_WINDOWS 0x0410   // 将此值更改为适当的值，以指定将 Windows Me 或更高版本作为目标。
#endif

#ifndef _WIN32_IE                   // 允许使用特定于 IE 6.0 或更高版本的功能。
    #define _WIN32_IE 0x0600        // 将此值更改为相应的值，以适用于 IE 的其他版本。
#endif

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN         // 从 Windows 头中排除极少使用的资料
#endif

// Windows 头文件:
//#define NOMINMAX      //std::min


//#include "buildcfg/buildcfg.h"
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <objbase.h>
#include <MMSystem.h>
#include <iostream>
#include <fstream> 
#include <iomanip>
#include <algorithm>
#include<cmath>
// TODO: 在此处引用程序需要的其他头文件
#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )
using namespace Gdiplus;
#pragma   comment(lib, "winmm.lib ")
//=========================
#include <windowsx.h>       // protect template members from windowsx.h macros (atlgdi.h)
#include <atlstr.h>         // CString
#include <atltypes.h>       // CSize, CPoint, CRect
#include <atlimage.h>
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#include <atlbase.h>        // CComModule, CRegKey, CHandle         
#include <atlapp.h>         // CAppModule, CTempBuffer, CIdleHandler, CMessageLoop
#include <atlmisc.h>        // WTL::CPoint, WTL::CFindFile
#include <atlcoll.h>        // CAtlArray, CAtlList, CAtlMap
#include <atlframe.h>
#include <atlcrack.h>
#include <atlgdi.h>
#include <atlfile.h>        // CAtlFileMapping
#include <atlcomcli.h>
#include <atlstr.h>			// CString
#include <atltypes.h>		// CSize, CPoint, CRect
#include <atlimage.h>
#include <atlsync.h>		// ATL::CCriticalSection, ATL::CEvent, ATL::CMutex, ATL::CMutexLock, ATL::CSemaphore
#include <shellapi.h>
#include <atlctrls.h>		// WTL::CImageList
#include <atlctrlx.h>
#include <atlscrl.h>		// WTL::CScrollImpl
#include <atldlgs.h>
#include <atlsimpcoll.h>	// CSimpleArray, CSimpleMap
#include <atltime.h>		// ATL::CTime, ATL::CTimeSpan, ATL::CFileTime
#include <atlpath.h>		// ATL::ATLPath, ATL::CPathT

#include <commctrl.h>       //CComPtr
#include <Shobjidl.h>       //ITaskbarList3
//
//#pragma warning(push)              // 仅禁用此头文件
#pragma warning(disable:4244)
#pragma warning(disable:4267)       // 从“size_t”转换到“DWORD
#pragma warning(disable:4996)       //  _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4311)       //   从“LPCTSTR”到“DWORD”的指针截断
#pragma warning(disable:4819)       //   该文件包含不能在当前代码页(936)中表示的字符
#pragma warning(disable:4018)       //   warning C4018: '<' : signed/unsigned mismatch

//#pragma warning(pop)              // 恢复最初的警告级别
#define CACTUS_DLL
// TODO: 在此处引用程序需要的其他头文件
#include <tracetool/tracetool.h>
#include <DuiLib/UIlib.h>
using namespace DuiLib;

#ifdef _DEBUG
    #ifdef _UNICODE
        #pragma comment(lib, "../../lib/win32d_md/DuiLib.lib")
        #pragma comment(lib, "../../lib/win32d_md/dgcore.lib")
        #pragma comment(lib, "../../lib/win32d_md/dgctrl.lib")
        #pragma comment(lib, "../../lib/win32d/cactus_dll_mdd.lib")
    #else
        #pragma comment(lib, "DuiLib_d.lib")
    #endif    
#else
    #ifdef _UNICODE
        #pragma comment(lib, "../../lib/win32_md/DuiLib.lib")
        #pragma comment(lib, "../../lib/win32_md/dgctrl.lib")
        #pragma comment(lib, "../../lib/win32_md/dgcore.lib")
        #pragma comment(lib, "../../lib/win32/cactus_dll_md.lib")

    #else
        #pragma comment(lib, "DuiLib.lib")
    #endif
#endif
