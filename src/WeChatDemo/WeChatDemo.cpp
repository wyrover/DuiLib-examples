// Copyright (c) 2016 Victor(516822434@qq.com)

// This code may be used in compiled form in any way you desire. These
// source files may be redistributed by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included.

// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
// Beware of bugs.


// WeChatDemo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WeChatDemo.h"

#include "MainWnd.h"

#include <atlbase.h>
#include <atlwin.h>

CComModule g_clComModule;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    /*CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin\\WeChatRes"));*/
    CPaintManagerUI::SetResourceType(UILIB_FILE);
    // 资源路径
    CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
    strResourcePath += _T("..\\skin\\WeChatRes\\");
    CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
    HINSTANCE hRichInstance = ::LoadLibrary(_T("Riched20.dll"));
    HRESULT hResult = ::CoInitialize(NULL);

    if (FAILED(hResult)) {
        ::FreeLibrary(hRichInstance);
        return 0;
    }

    hResult = ::OleInitialize(NULL);

    if (FAILED(hResult)) {
        ::CoUninitialize();
        ::FreeLibrary(hRichInstance);
        return 0;
    }

    g_clComModule.Init(0, hInstance);
    CMainWnd *pclMainWnd = new CMainWnd();

    if (pclMainWnd == NULL) {
        g_clComModule.Term();
        ::OleUninitialize();
        ::CoUninitialize();
        ::FreeLibrary(hRichInstance);
        return 0;
    }

    pclMainWnd->Create(NULL, _T("WeChatDemo"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pclMainWnd->CenterWindow();
    pclMainWnd->ShowWindow(true);
    CPaintManagerUI::MessageLoop();
    delete pclMainWnd;
    pclMainWnd = NULL;
    g_clComModule.Term();
    ::OleUninitialize();
    ::CoUninitialize();
    ::FreeLibrary(hRichInstance);
    return 0;
}