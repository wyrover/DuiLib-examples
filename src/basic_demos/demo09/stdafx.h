// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>

#include <tchar.h>
#include <objbase.h>
#include <string>


#include <shellapi.h>


#include "..\DuiLib\UIlib.h"
using namespace DuiLib;


typedef std::basic_string<TCHAR> tString;

#define USE(FEATURE) (defined USE_##FEATURE  && USE_##FEATURE)
#define ENABLE(FEATURE) (defined ENABLE_##FEATURE  && ENABLE_##FEATURE)

#define USE_ZIP_SKIN 1
#define USE_EMBEDED_RESOURCE 1
