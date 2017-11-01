#include "stdafx.h"
#include "ContactsList.h"

namespace DuiLib
{

CContactsListUI::CContactsListUI(CPaintManagerUI *pclPaintManager)
    : m_pclRoot(NULL)
    , m_iDelayDeltaY(0)
    , m_iDelayNumber(0)
    , m_iDelayLeft(0)
    , m_strLevelExpandImg(_T(""))
    , m_strLevelCollapseImg(_T(""))
    , m_iLevelTextStartPos(10)
    , m_clTextPadding(10, 0, 0, 0)
    , m_pclPaintManager(pclPaintManager)
{
    m_pclRoot = new CNode;
    m_pclRoot->GetData().m_iLevel = -1;
    m_pclRoot->GetData().m_bChildVisible = true;
    m_pclRoot->GetData().m_bHasChild = true;
    m_pclRoot->GetData().m_pclListElement = NULL;
}

CContactsListUI::~CContactsListUI()
{
    if (m_pclRoot != NULL) {
        delete m_pclRoot;
        m_pclRoot = NULL;
    }
}

bool CContactsListUI::Add(CControlUI *pclControl)
{
    if (pclControl == NULL) {
        return false;
    }

    if (_tcsicmp(pclControl->GetClass(), _T("ListContainerElementUI")) == 0) {
        return false;
    }

    return CListUI::Add(pclControl);
}

bool CContactsListUI::AddAt(CControlUI *pclControl, int iIndex)
{
    if (pclControl == NULL) {
        return false;
    }

    if (_tcsicmp(pclControl->GetClass(), _T("ListContainerElementUI")) == 0) {
        return false;
    }

    return CListUI::AddAt(pclControl, iIndex);
}

bool CContactsListUI::Remove(CControlUI *pclControl)
{
    if (pclControl == NULL) {
        return false;
    }

    if (_tcsicmp(pclControl->GetClass(), _T("ListContainerElementUI")) == 0) {
        return false;
    }

    return CListUI::Remove(pclControl);
}

bool CContactsListUI::RemoveAt(int iIndex)
{
    CControlUI *pclControl = GetItemAt(iIndex);

    if (pclControl == NULL) {
        return false;
    }

    if (_tcsicmp(pclControl->GetClass(), _T("ListContainerElementUI")) == 0) {
        return false;
    }

    return CListUI::RemoveAt(iIndex);
}

void CContactsListUI::RemoveAll()
{
    CListUI::RemoveAll();

    if (m_pclRoot != NULL) {
        delete m_pclRoot;
        m_pclRoot = NULL;
    }

    m_pclRoot = new CNode;
    m_pclRoot->GetData().m_iLevel = -1;
    m_pclRoot->GetData().m_bChildVisible = true;
    m_pclRoot->GetData().m_bHasChild = true;
    m_pclRoot->GetData().m_pclListElement = NULL;
}

void CContactsListUI::DoEvent(TEventUI &stEvent)
{
    if (!IsMouseEnabled() && (stEvent.Type > UIEVENT__MOUSEBEGIN) && (stEvent.Type < UIEVENT__MOUSEEND)) {
        if (m_pParent != NULL) {
            m_pParent->DoEvent(stEvent);
        } else {
            CVerticalLayoutUI::DoEvent(stEvent);
        }

        return;
    }

    if ((stEvent.Type == UIEVENT_TIMER) && (stEvent.wParam == SCROLL_TIMERID)) {
        if (m_iDelayLeft > 0) {
            --m_iDelayLeft;
            SIZE stPos = GetScrollPos();
            LONG lDeltaY = (LONG)(CalculateDelay((double)m_iDelayLeft / m_iDelayNumber) * m_iDelayDeltaY);

            if (((lDeltaY > 0) && (stPos.cy != 0)) || ((lDeltaY < 0) && (stPos.cy != GetScrollRange().cy))) {
                stPos.cy -= lDeltaY;
                SetScrollPos(stPos);
                return;
            }
        }

        m_iDelayDeltaY = 0;
        m_iDelayNumber = 0;
        m_iDelayLeft = 0;
        m_pManager->KillTimer(this, SCROLL_TIMERID);
        return;
    }

    if (stEvent.Type == UIEVENT_SCROLLWHEEL) {
        LONG lDeltaY = 0;

        if (m_iDelayNumber > 0) {
            lDeltaY = (LONG)(CalculateDelay((double)m_iDelayLeft / m_iDelayNumber) * m_iDelayDeltaY);
        }

        switch (LOWORD(stEvent.wParam)) {
        case SB_LINEUP:
            if (m_iDelayDeltaY >= 0) {
                m_iDelayDeltaY = lDeltaY + 8;
            } else {
                m_iDelayDeltaY = lDeltaY + 12;
            }

            break;

        case SB_LINEDOWN:
            if (m_iDelayDeltaY <= 0) {
                m_iDelayDeltaY = lDeltaY - 8;
            } else {
                m_iDelayDeltaY = lDeltaY - 12;
            }

            break;
        }

        if (m_iDelayDeltaY > 100) {
            m_iDelayDeltaY = 100;
        } else if (m_iDelayDeltaY < -100) {
            m_iDelayDeltaY = -100;
        }

        m_iDelayNumber = (DWORD)sqrt((double)abs(m_iDelayDeltaY)) * 5;
        m_iDelayLeft = m_iDelayNumber;
        m_pManager->SetTimer(this, SCROLL_TIMERID, 50U);
        return;
    }

    CListUI::DoEvent(stEvent);
}

CNode *CContactsListUI::GetRoot()
{
    return m_pclRoot;
}

CNode * CContactsListUI::AddNode(const tagContactsInfo &stItemInfo, CNode *pclParent)
{
    if (pclParent == NULL) {
        pclParent = m_pclRoot;
    }

    TCHAR szBuffer[MAX_PATH] = {0};
    CListContainerElementUI *pclListElement = NULL;

    if (!m_clDlgBuilder.GetMarkup()->IsValid()) {
        pclListElement = static_cast<CListContainerElementUI *>(m_clDlgBuilder.Create(_T("contactslistitem.xml"), (UINT)0, NULL, m_pclPaintManager));
    } else {
        pclListElement = static_cast<CListContainerElementUI *>(m_clDlgBuilder.Create((UINT)0, m_pclPaintManager));
    }

    if (pclListElement == NULL) {
        return NULL;
    }

    CNode *pclNode = new CNode;
    pclNode->GetData().m_iLevel = pclParent->GetData().m_iLevel + 1;

    if (stItemInfo.m_bIsFolder) {
        pclNode->GetData().m_bHasChild = !stItemInfo.m_bIsEmpty;
    } else {
        pclNode->GetData().m_bHasChild = false;
    }

    pclNode->GetData().m_bIsFolder = stItemInfo.m_bIsFolder;
    pclNode->GetData().m_bChildVisible = (pclNode->GetData().m_iLevel == 0);
    pclNode->GetData().m_iType = stItemInfo.m_iType;
    pclNode->GetData().m_strText = stItemInfo.m_strName;
    pclNode->GetData().m_strValue = stItemInfo.m_strID;
    pclNode->GetData().m_pclListElement = pclListElement;

    if (!pclParent->GetData().m_bChildVisible) {
        pclListElement->SetVisible(false);
    }

    if ((pclParent != m_pclRoot) && !pclParent->GetData().m_pclListElement->IsVisible()) {
        pclListElement->SetVisible(false);
    }

    if (stItemInfo.m_bIsFolder) {
        CContainerUI *pclLogoContainer = (CContainerUI *)m_pclPaintManager->FindSubControlByName(pclListElement, L"logo_container");

        if (pclLogoContainer != NULL) {
            pclLogoContainer->SetVisible(false);
        }
    } else {
        CControlUI *pclLogo = (CControlUI *)m_pclPaintManager->FindSubControlByName(pclListElement, L"logo");

        if (pclLogo != NULL) {
            pclLogo->SetBkImage(stItemInfo.m_strIDIco.c_str());
        }
    }

    CLabelUI *pclName = (CLabelUI *)m_pclPaintManager->FindSubControlByName(pclListElement, L"nickname");

    if (pclName != NULL) {
        pclName->SetText(stItemInfo.m_strName.c_str());
    }

    pclListElement->SetTag((UINT_PTR)pclNode);
    int iIndex = 0;

    if (pclParent->HasChild()) {
        CNode *pclPreNode = pclParent->GetLastChild();
        iIndex = pclPreNode->GetData().m_pclListElement->GetIndex() + 1;
    } else {
        if (pclParent == m_pclRoot) {
            iIndex = 0;
        } else {
            iIndex = pclParent->GetData().m_pclListElement->GetIndex() + 1;
        }
    }

    if (stItemInfo.m_bIsFolder) {
        pclListElement->SetFixedHeight(25);
        RECT stRect = pclName->GetPadding();
        stRect.top = -2;
        pclName->SetPadding(stRect);
        pclName->SetTextColor(0XFFADADAD);
    } else {
        pclListElement->SetBkColor(0XFF3A3A3A);
    }

    if (!CListUI::AddAt(pclListElement, iIndex)) {
        delete pclListElement;
        pclListElement = NULL;
        delete pclNode;
        pclNode = NULL;
    }

    pclParent->AddChild(pclNode);
    return pclNode;
}

void CContactsListUI::RemoveNode(CNode *pclNode)
{
    if ((pclNode == NULL) || (pclNode == m_pclRoot)) {
        return;
    }

    for (int i = 0; i < pclNode->GetChildrenCount(); ++i) {
        CNode *pclChild = pclNode->GetChild(i);
        RemoveNode(pclChild);
    }

    CListUI::Remove(pclNode->GetData().m_pclListElement);
    delete pclNode->GetData().m_pclListElement;
    pclNode->GetData().m_pclListElement = NULL;
    pclNode->GetParent()->RemoveChild(pclNode);
    delete pclNode;
    pclNode = NULL;
}

void CContactsListUI::SetChildVisible(CNode *pclNode, bool bVisible)
{
    if ((pclNode == NULL) || (pclNode == m_pclRoot)) {
        return;
    }

    if (pclNode->GetData().m_bChildVisible == bVisible) {
        return;
    }

    pclNode->GetData().m_bChildVisible = bVisible;

    if (!pclNode->GetData().m_pclListElement->IsVisible()) {
        return;
    }

    if (!pclNode->HasChild()) {
        return;
    }

    CNode *pclBegin = pclNode->GetChild(0);
    CNode *pclEnd = pclNode->GetLastChild();

    for (int i = pclBegin->GetData().m_pclListElement->GetIndex(); i <= pclEnd->GetData().m_pclListElement->GetIndex(); ++i) {
        CControlUI *pclControl = GetItemAt(i);

        if (_tcsicmp(pclControl->GetClass(), _T("ListContainerElementUI")) == 0) {
            if (bVisible) {
                CNode *pclLocalParent = ((CNode*)pclControl->GetTag())->GetParent();

                if (pclLocalParent->GetData().m_bChildVisible && pclLocalParent->GetData().m_pclListElement->IsVisible()) {
                    pclControl->SetVisible(true);
                }
            } else {
                pclControl->SetVisible(false);
            }
        }
    }
}

bool CContactsListUI::IsExpandable(CNode *pclNode) const
{
    if ((pclNode == NULL) || (pclNode == m_pclRoot)) {
        return false;
    }

    return pclNode->GetData().m_bHasChild;
}

} // namespace DuiLib