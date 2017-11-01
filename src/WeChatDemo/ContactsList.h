#ifndef __CONTACTSLIST_H
#define __CONTACTSLIST_H

#include "Node.h"

namespace DuiLib
{
struct tagContactsInfo {
    bool m_bIsFolder;
    bool m_bIsEmpty;
    int m_iType; // 1-普通联系人 2-公众号 3-订阅号
    STLString m_strID;
    STLString m_strIDIco;
    STLString m_strName;
};

class CContactsListUI : public CListUI
{
public:
    enum {SCROLL_TIMERID = 10};

    CContactsListUI(CPaintManagerUI *pclPaintManager);
    ~CContactsListUI();

    bool Add(CControlUI *pclControl);
    bool AddAt(CControlUI *pclControl, int iIndex);

    bool Remove(CControlUI *pclControl);
    bool RemoveAt(int iIndex);
    void RemoveAll();

    void DoEvent(TEventUI &event);

    CNode *GetRoot();
    CNode *AddNode(const tagContactsInfo &stItem, CNode *pclParent = NULL);
    void RemoveNode(CNode *pclNode);

    void SetChildVisible(CNode *pclNode, bool bVisible);

    bool IsExpandable(CNode *pclNode) const;
private:
    CNode *m_pclRoot;
    LONG m_iDelayDeltaY;
    DWORD m_iDelayNumber;
    DWORD m_iDelayLeft;
    CDuiRect m_clTextPadding;
    int m_iLevelTextStartPos;
    STLString m_strLevelExpandImg;
    STLString m_strLevelCollapseImg;

    CPaintManagerUI *m_pclPaintManager;
    CDialogBuilder m_clDlgBuilder;
};

} // DuiLib

#endif // __CONTACTSLIST_H