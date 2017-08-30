#include "stdafx.h"
#include "MainFrm.h"

int APIENTRY
_tWinMain(HINSTANCE hInstance,
          HINSTANCE /*hPrevInstance*/,
          LPTSTR    lpCmdLine,
          int       nCmdShow)
{
    TRACE_CLEAR;

    CPaintManagerUI::SetInstance(hInstance);
    //CPaintManagerUI::SetResourceDll();
    //if (!CPaintManagerUI::LoadPlugin(DGCTRLS_MODULE)) break;

    boost::scoped_ptr<CMainFrm> pMainFrm(new CMainFrm());
    if (pMainFrm == NULL) return -1;

    pMainFrm->Create((HWND)NULL, _T("Çý¶¯¾«Áé"), WS_OVERLAPPEDWINDOW, NULL);
    pMainFrm->SetIcon(IDI_DGMAIN);
    pMainFrm->CenterWindow();

    CPaintManagerUI::MessageLoop();
    CPaintManagerUI::Term();

	::CoUninitialize();
    return 0;
}


