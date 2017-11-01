
#ifndef __UI_BASE_WND_H__
#define __UI_BASE_WND_H__

namespace DG
{
namespace UI
{

class CBaseWnd : public WindowImplBase
{
public:
    CBaseWnd();
    virtual ~CBaseWnd();

    void CenterScreen(bool byOwner = false);

    HWND Create(CBaseWnd *pParent, LPCTSTR lpszTitle, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT)
    {
        m_pParentWnd = pParent;
        return __super::Create(pParent ? pParent->GetHWND() : NULL, lpszTitle, dwStyle, dwExStyle, x, y, cx, cy);
    }
    HWND Create(HWND hWndParent, LPCTSTR lpszTitle, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT)
    {
        m_pParentWnd = NULL;
        return __super::Create(hWndParent, lpszTitle, dwStyle, dwExStyle, x, y, cx, cy);
    }
protected:
    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    bool m_bShadow;
    CShadowUI   m_shadowui;
    CBaseWnd*   m_pParentWnd;
};



} // namespace UI
} // namespace DGHelper




#endif //__UI_BASE_WND_H__