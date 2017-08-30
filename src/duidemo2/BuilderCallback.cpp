
#include "stdafx.h"
#include "BuilderCallback.h"

#include <Duilib/Control/UIEdit.h>
#include <DuiLib/Control/UICombo.h>

#include <string>
#include "boost/foreach.hpp"
#include <boost/math/special_functions/round.hpp>
#include "boost/smart_ptr.hpp"

//////////////////////////////////////////////////////////////////////////
CLabelUI *pFrequenceLabel = NULL;

CListElemUI::CListElemUI()
    : m_bRunning(false)
{}

CListElemUI::~CListElemUI()
{

}

void CListElemUI::safe_animator_update(boost::weak_ptr<CListElemUI> wpElem)
{
    boost::shared_ptr<CListElemUI> spItem(wpElem.lock());
    if (spItem) {
        spItem->animator_update();
    }
}

void CListElemUI::safe_animator_complete(boost::weak_ptr<CListElemUI> wpElem)
{
    boost::shared_ptr<CListElemUI> spItem(wpElem.lock());
    if (spItem) {
        spItem->animator_complate();
    }
}
void CListElemUI::Init()
{
    boost::weak_ptr<CListElemUI> weak_this = boost::weak_ptr<CListElemUI>(shared_from_this());

    animator_.reset(new DuiLib::Animator2());         
    //animator_->set_update_callback(boost::bind(&CListElemUI::animator_update, this());
    //animator_->set_complete_callback(boost::bind(&CListElemUI::animator_complate, this());
    animator_->set_update_callback(boost::bind(&CListElemUI::safe_animator_update, weak_this));
    animator_->set_complete_callback(boost::bind(&CListElemUI::safe_animator_complete, weak_this));
    animator_->set_interval(2000);
    animator_->set_reverse(true);
    animator_->set_tweener(tween::LINEAR, tween::EASE_IN_OUT);
    animator_->set_name(this->GetInterfaceName());

    if (pFrequenceLabel == NULL){
        pFrequenceLabel = (CLabelUI*)m_pManager->FindControl(L"frequence_label");
    }

    LPVOID ctrls[] = {&m_pProgress, &m_pState, &m_pInterval};

    for (int i = 0; i < ARRAYSIZE(ctrls) ; i++) {
        CControlUI* pControl = GetItemAt(i);
        if (pControl) {
            CControlUI** p = (CControlUI**)ctrls[i];
            (*p) = pControl;
        }
    }
}

void CListElemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    CListContainerElementUI::SetAttribute(pstrName, pstrValue);
}

void CListElemUI::DoEvent(TEventUI& event)
{
    if( event.Type == UIEVENT_INITCONTROLS ){
    } else if( event.Type == UIEVENT_TIMER ){

        return;
    }

    return CListContainerElementUI::DoEvent(event);
}


void CListElemUI::Start()
{
    m_pState->SetText(L"...");
    CString str;
    str.Format(L"%d:%d", 0, m_nInterval);
    m_nStartTime = time(NULL);
    m_pInterval->SetText(str);
    m_bRunning = true;
    animator_->set_start_value(0);
    animator_->set_end_value(100);
    animator_->start();
}

void CListElemUI::Stop()
{
    animator_->end();
}

void CListElemUI::Pause()
{
    animator_->pause();
}

void CListElemUI::SetInterval(int interval)
{
    m_nInterval = interval / 1000;
    animator_->set_interval(interval);
}

void CListElemUI::animator_update()
{
    if (animator_ && animator_->is_running()) {
        TCHAR szBuf[MAX_PATH] = {0};
        _stprintf(szBuf, L"%I64d:%2d", time(NULL)-m_nStartTime, m_nInterval);
        m_pInterval->SetText(szBuf);

        _stprintf(szBuf, L"%.1lffps", animator_->get_frequence());
        pFrequenceLabel->SetText(szBuf);

        int nCurrentValue = (int)boost::math::round(animator_->get_value());
        m_pProgress->SetValue(nCurrentValue);
    }
}

void CListElemUI::animator_complate()
{
    CString str;
    str.Format(L"%I64d:%d", time(NULL) - m_nStartTime, m_nInterval);
    m_pInterval->SetText(str);
    m_pProgress->SetValue(m_pProgress->GetMaxValue());
    m_pState->SetText(L"OK");
}

void CListElemUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
    CListContainerElementUI::DoPaint(hDC, rcPaint);
}

//////////////////////////////////////////////////////////////////////////

CMyListBodyUI::CMyListBodyUI(CListUI* pOwner)
:CListBodyUI(pOwner)
{
    ASSERT(m_pOwner);
}

void CMyListBodyUI::SetScrollPos(SIZE szPos)
{
    int cx = 0;
    int cy = 0;
    if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) {
        int iLastScrollPos = m_pVerticalScrollBar->GetScrollPos();
        m_pVerticalScrollBar->SetScrollPos(szPos.cy);
        cy = m_pVerticalScrollBar->GetScrollPos() - iLastScrollPos;
    }

    if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) {
        int iLastScrollPos = m_pHorizontalScrollBar->GetScrollPos();
        m_pHorizontalScrollBar->SetScrollPos(szPos.cx);
        cx = m_pHorizontalScrollBar->GetScrollPos() - iLastScrollPos;
    }

    if( cx == 0 && cy == 0 ) return;

    RECT rcPos;
    for( int it2 = 0; it2 < m_items.GetSize(); it2++ ) {
        CControlUI* pControl = static_cast<CControlUI*>(m_items[it2]);
        if( !pControl->IsVisible() ) continue;
        //	if( pControl->IsFloat() ) continue;

        rcPos = pControl->GetPos();
        rcPos.left -= cx;
        rcPos.right -= cx;
        rcPos.top -= cy;
        rcPos.bottom -= cy;
        pControl->SetPos(rcPos);
    }

    Invalidate();

    if( cx != 0 && m_pOwner ) {
        CListHeaderUI* pHeader = m_pOwner->GetHeader();
        if( pHeader == NULL ) return;
        TListInfoUI* pInfo = m_pOwner->GetListInfo();
        pInfo->nColumns = min(pHeader->GetCount(), UILIST_MAX_COLUMNS);

        if( !pHeader->IsVisible() ) {
            for( int it = 0; it < pHeader->GetCount(); it++ ) {
                static_cast<CControlUI*>(pHeader->GetItemAt(it))->SetInternVisible(true);
            }
        }
        for( int i = 0; i < pInfo->nColumns; i++ ) {
            CControlUI* pControl = static_cast<CControlUI*>(pHeader->GetItemAt(i));
            if( !pControl->IsVisible() ) continue;
            if( pControl->IsFloat() ) continue;

            RECT rcPos = pControl->GetPos();
            rcPos.left -= cx;
            rcPos.right -= cx;
            pControl->SetPos(rcPos);
            pInfo->rcColumn[i] = pControl->GetPos();
        }
        if( !pHeader->IsVisible() ) {
            for( int it = 0; it < pHeader->GetCount(); it++ ) {
                static_cast<CControlUI*>(pHeader->GetItemAt(it))->SetInternVisible(false);
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////

CMyListUI::CMyListUI()
: m_bScrollMsgSended(false)
{
    CVerticalLayoutUI::RemoveAll();
    m_pList = new CMyListBodyUI(this);

    m_pHeader = new CListHeaderUI;

    Add(m_pHeader);
    CVerticalLayoutUI::Add(m_pList);
}	

void CMyListUI::DoEvent(TEventUI& event)
{
    __super::DoEvent(event);
}

void CMyListUI::SendScrollMsg()
{
    if( m_scrollallback) {
        if (GetVerticalScrollBar()) {
            GetVerticalScrollBar()->OnNotify.Empty();
        }
        m_scrollallback();
        m_scrollallback.clear();
    }
}

void CMyListUI::SetScrollCallbackOnce(boost::function<void(void)> func)
{
    if (!m_scrollallback) {
        if (GetVerticalScrollBar()) {
            GetVerticalScrollBar()->OnNotify.Empty();
            GetVerticalScrollBar()->OnNotify += MakeDelegate(this, &CMyListUI::OnScrollNotify);
        }
    }

    m_scrollallback = func;
}

void CMyListUI::SetScrollPos(SIZE szPos)
{
    SendScrollMsg();
    __super::SetScrollPos(szPos);
}

void CMyListUI::ProcessScrollBar(RECT rc, int cxRequired, int cyRequired)
{
    return __super::ProcessScrollBar(rc, cxRequired, cyRequired);
}

bool CMyListUI::OnScrollNotify(void* param)
{
    DuiLib::TNotifyUI* pMsg = (DuiLib::TNotifyUI*)param;
    if (pMsg->sType == DUI_MSGTYPE_SCROLL){
        SendScrollMsg();
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
CControlUI* CDuiCallback::CreateControl(LPCTSTR pstrClass) 
{
    return StaticCreateControl(pstrClass);
}

DuiLib::CControlUI* CDuiCallback::StaticCreateControl(LPCTSTR pstrClass)
{
    if (_tcscmp(pstrClass, _T("ListElem")) == 0) return new CListElemUI;
    if (_tcscmp(pstrClass, _T("MyList")) == 0) return new CMyListUI;
    return NULL;
}
