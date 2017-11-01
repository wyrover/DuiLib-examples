#include "stdafx.h"

#include <boost/foreach.hpp>
#include "boost/format.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "MainFrm.h"
#include "BuilderCallback.h"

#define DUI_SET_CTR(ptr, id) \
    { CControlUI** p = (CControlUI**)&ptr;      \
        *p = m_pm.FindControl(id);  }


DuiLib::CTabLayoutUI *pTab;
DuiLib::CButtonUI *pTestUnloadButton;
DuiLib::CLabelUI *pUnloadLabel;
DuiLib::CButtonUI *pChangeTabButton;
DuiLib::CButtonUI *pPosLabel;
DuiLib::CButtonUI *pXYLabel;
DuiLib::CLabelUI *pTargetLabel;

CMyListUI *pList;
std::vector<boost::shared_ptr<CListElemUI>>  vItems;

CMainFrm::CMainFrm()
{
}

CMainFrm::~CMainFrm()
{
}

DUI_BEGIN_MESSAGE_MAP(CMainFrm, DuiLib::WindowImplBase)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,           OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_VALUECHANGED,    OnValueChanged)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SCROLL,          OnScroll)
DUI_END_MESSAGE_MAP()

boost::recursive_mutex                        rec_mutex_;
void do_lock_recursive_mutex()
{
    boost::recursive_mutex::scoped_lock lock(rec_mutex_);
    {
        boost::recursive_mutex::scoped_lock lock(rec_mutex_);
        {
            boost::recursive_mutex::scoped_lock lock(rec_mutex_);
            ::Sleep(10000);
            lock.unlock();
        }
        lock.unlock();
    }
    lock.unlock();
}

void CMainFrm::InitWindow()
{
    ShowWindow();
    CenterWindow();
    ::SetForegroundWindow(m_hWnd);
    DUI_SET_CTR(pTab, _T("main_tab"));
    DUI_SET_CTR(pTestUnloadButton, _T("test_unload_control"));
    DUI_SET_CTR(pUnloadLabel, _T("unload_label"));
    DUI_SET_CTR(pChangeTabButton, _T("change_tab"));
    DUI_SET_CTR(pPosLabel, _T("pos_label"));
    DUI_SET_CTR(pXYLabel, _T("xy_label"));
    DUI_SET_CTR(pTargetLabel, _T("target_label"));
    DUI_SET_CTR(pList, _T("list_ctrl"));
    pList->GetList()->SetSelfManaged(true);
    pList->GetList()->SetDelayedDestroy(false);
    //boost::thread t(&do_lock_recursive_mutex);
    //::Sleep(5000);
    //boost::recursive_mutex::scoped_lock lock(rec_mutex_);
    //lock.unlock();
    boost::shared_ptr<int> sp(new int(10));
    assert(sp.use_count() == 1);
    boost::weak_ptr<int> wp(sp);
    assert(sp.use_count() == 1);
    boost::shared_ptr<int> sp2 = sp;
    assert(sp.use_count() == 2);
    //sp.reset()
}

void CMainFrm::Notify(TNotifyUI& msg)
{
    // DISPATCH_HANDLER_CALLBACK(msg);
    __super::Notify(msg);
}
//////////////////////////////////////////////////////////////////////////
// 1. 未SetPos的控件 GetPos 值无效
// 2. SetFixedXY后必须调用 NeedParentUpdate
// 3. SetFixedXY后更新位置时，如果是float控件，只会更新自身，此时如果控件时显示状态的话，
//    仅仅是执行 pUpdateControl->SetPos( pUpdateControl->GetPos() ); 所以SetFixedXY无效
//    float控件的位置更新，需要主动通知父控件，父控件SetPos 时会对于浮动控件会调用SetFloatPos, 非浮动控件调用SetPos
//    对于  如果是非float控件，则会通知父控件更新子控件
// 4. SetFixedXY对非浮动控件无效
// 5. SetFixedXY X：位置相对于顶部，Y：相对于底部，用移动盲区
// 6. 必要时配置 SetPos 使用，在全范围内移动

//  void CContainerUI::SetPos(RECT rc)
//  void CContainerUI::SetFloatPos(int index)
//  void CControlUI::NeedUpdate()
//  void CControlUI::NeedParentUpdate()
//  UIManager::@676 WM_PAINT m_bUpdateNeeded

void CMainFrm::OnClick(TNotifyUI& msg)
{
    CDuiString sCtrlName = msg.pSender->GetName();
    CDuiString sCtrlUdata = msg.pSender->GetUserData();
    bool bHandled = false;

    if (sCtrlName == _T("get_fixed_xy_btn")) {
        CString strPos;
        SIZE szPos = pTargetLabel->GetFixedXY();
        strPos.Format(L"XY: %d,%d", szPos.cx, szPos.cy);
        pXYLabel->SetText(strPos);
    } else if (sCtrlName == _T("set_fixed_xy_btn")) {
        SIZE szPos = pTargetLabel->GetFixedXY();
        SIZE sz = {szPos.cx - 20, szPos.cy - 20};
        pTargetLabel->SetFixedXY(sz);
        //pTargetLabel->NeedParentUpdate();
        CContainerUI *pContainer = (CContainerUI *) pTargetLabel->GetParent();
        pContainer ->SetFloatPos(pTargetLabel);
        //pTargetLabel->NeedUpdate();
    } else if (sCtrlName == _T("get_pos_btn")) {
        CString strPos;
        RECT rcPos = pTargetLabel->GetPos();
        strPos.Format(L"POS: %d,%d,%d,%d", rcPos.left, rcPos.top, rcPos.right, rcPos.bottom);
        pPosLabel->SetText(strPos);
    } else if (sCtrlName == _T("set_pos_btn")) {
        RECT rc = {0};
        RECT rcNow = pTargetLabel->GetPos();
        rc.left = rcNow.left + 5;
        rc.top = rcNow.top + 5;
        rc.right = rc.left + pTargetLabel->GetFixedWidth();
        rc.bottom = rc.top + pTargetLabel->GetFixedHeight();
        pTargetLabel->SetPos(rc);
    } else if (sCtrlName == _T("reset_pos_btn")) {
        RECT rc = {0};
        rc.left = 0;
        rc.top = 0;
        rc.right = rc.left + pTargetLabel->GetFixedWidth();
        rc.bottom = rc.top + pTargetLabel->GetFixedHeight();
        pTargetLabel->SetPos(rc);
    } else if (sCtrlName == _T("toogle_float_btn")) {
        pTargetLabel->SetFloat(!pTargetLabel->IsFloat());
    } else if (sCtrlName == _T("toogle_visible_btn")) {
        pTargetLabel->SetVisible(!pTargetLabel->IsVisible());
    } else if (sCtrlName == _T("change_tab")) {
        pTab->SelectItem((pTab->GetCurSel() + 1) % pTab->GetCount());
    } else if (sCtrlName == _T("init_btn")) {
        CDuiCallback cb;

        for (int i = 0; i < 1500 ; i++) {
            CDialogBuilder builder;
            boost::shared_ptr<CListElemUI> pItem((CListElemUI*)builder.Create(L"list_item.xml", NULL, &cb));
            pList->Add(pItem.get());
            pItem->Init();
            vItems.push_back(pItem);
        }
    } else if (sCtrlName == _T("remove_btn")) {
        CDuiCallback cb;

        for (int i = pList->GetCount() - 1; i >= 0 ; i--) {
            CListElemUI* pItem = (CListElemUI*)pList->GetItemAt(i);
            pItem->Stop();
            pList->RemoveAt(i);
        }

        vItems.clear();
    } else if (sCtrlName == _T("start_btn")) {
        for (int i = 0; i < pList->GetCount() ; i++) {
            CListElemUI* pItem = (CListElemUI*)pList->GetItemAt(i);
            pItem->SetInterval(i * 1000);
            pItem->Start();
        }
    } else if (sCtrlName == _T("pause_btn")) {
        // pList->RemoveAll();
        for (int i = 0; i < pList->GetCount() ; i++) {
            CListElemUI* pItem = (CListElemUI*)pList->GetItemAt(i);
            pItem->Pause();
        }
    } else if (sCtrlName == _T("end_btn")) {
        // pList->RemoveAll();
        for (int i = 0; i < pList->GetCount() ; i++) {
            CListElemUI* pItem = (CListElemUI*)pList->GetItemAt(i);
            pItem->Stop();
        }
    }

    if (!bHandled) __super::OnClick(msg);
}

void CMainFrm::OnValueChanged(TNotifyUI& msg)
{
    CDuiString sCtrlName = msg.pSender->GetName();
    CDuiString sCtrlUdata = msg.pSender->GetUserData();
}

void CMainFrm::OnScroll(TNotifyUI& msg)
{
}

//////////////////////////////////////////////////////////////////////////
LRESULT CMainFrm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = TRUE;
    ::DestroyWindow(*this);
    return 0;
}

LRESULT CMainFrm::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    ::PostQuitMessage(0L);
    return 0;
}

LRESULT CMainFrm::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return TRUE;
}

LRESULT CMainFrm::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt;
    pt.x = GET_X_LPARAM(lParam);
    pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);
    RECT rcClient;
    ::GetClientRect(*this, &rcClient);

    // 屏蔽主窗口的 横向拉伸
    if (!::IsZoomed(*this)) {
        RECT rcSizeBox = m_pm.GetSizeBox();
        rcClient.left += rcSizeBox.left;
        rcClient.top += rcSizeBox.top;
        rcClient.bottom -= rcSizeBox.bottom;
        rcClient.right -= rcSizeBox.right;

        if (FALSE == ::PtInRect(&rcClient, pt)) {
            return HTCLIENT;
        }
    }

    return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
}

LRESULT CMainFrm::OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    COPYDATASTRUCT* lpCopy = (COPYDATASTRUCT*)lParam;
    bHandled = TRUE;
    return TRUE;
}

LRESULT CMainFrm::HandleCustomMessage(
    UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    switch (uMsg) {
    case WM_TIMER:
        OnTimer(uMsg, wParam, lParam, bHandled);
        break;

    default:
        break;
    }

    bHandled = FALSE;
    return 0;
}