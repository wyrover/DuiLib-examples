#include "stdafx.h"
#include "drivergenius/ui/BaseWnd.h"
//#include "drivergenius/ui/BuilderCallback.h"
#include "drivergenius/def/def.h"

namespace DG
{
namespace UI
{

CBaseWnd::CBaseWnd()
    : m_bShadow(true)
{

};

CBaseWnd::~CBaseWnd()
{

};

LRESULT CBaseWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //m_ShadowWnd.ParentProc(*this, uMsg, wParam, lParam);
    m_shadowui.ParentProc(*this, uMsg, wParam, lParam);

    return __super::HandleMessage(uMsg, wParam, lParam);


}

LRESULT CBaseWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //先初始化窗口，再获取阴影数据
    m_shadowui.Create(m_hWnd, &m_PaintManager);
    LRESULT lres = __super::OnCreate(uMsg, wParam, lParam, bHandled);
    
    m_shadowui.CopyShadow(m_PaintManager.GetShadow());

    return lres;
}


void CBaseWnd::CenterScreen(bool byOwner)
{
    if (byOwner) {
        return this->CenterWindow();
    } else {
        ASSERT(::IsWindow(m_hWnd));
        ASSERT((GetWindowStyle(m_hWnd)&WS_CHILD) == 0);
        RECT rcDlg = { 0 };
        ::GetWindowRect(m_hWnd, &rcDlg);
        RECT rcArea = { 0 };
        RECT rcCenter = { 0 };
        HWND hWnd = *this;
        HWND hWndCenter = NULL;

        // 处理多显示器模式下屏幕居中
        MONITORINFO oMonitor = {};
        oMonitor.cbSize = sizeof(oMonitor);
        ::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &oMonitor);
        rcArea = oMonitor.rcWork;

        if (hWndCenter == NULL)
            rcCenter = rcArea;

        int DlgWidth = rcDlg.right - rcDlg.left;
        int DlgHeight = rcDlg.bottom - rcDlg.top;

        // Find dialog's upper left based on rcCenter
        int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
        int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

        // The dialog is outside the screen, move it inside
        if (xLeft < rcArea.left) xLeft = rcArea.left;
        else if (xLeft + DlgWidth > rcArea.right) xLeft = rcArea.right - DlgWidth;

        if (yTop < rcArea.top) yTop = rcArea.top;
        else if (yTop + DlgHeight > rcArea.bottom) yTop = rcArea.bottom - DlgHeight;

        ::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

} // namespace UI
} // namespace DGHelper