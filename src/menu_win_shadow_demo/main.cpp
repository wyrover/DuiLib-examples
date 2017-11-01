#include "duilib.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    ::CoInitialize(NULL);
    // 资源类型
    CPaintManagerUI::SetResourceType(UILIB_FILE);
    // 资源路径
    CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
    strResourcePath += _T("..\\skin\\menu_win_shadow_demo\\");
    CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
    CFrameWnd *pFrame = new CFrameWnd(_T("Main_dlg.xml"));
    pFrame->Create(NULL, _T("Redrain菜单Demo"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowModal();
    delete pFrame;
    ::CoUninitialize();
    return 0;
}
