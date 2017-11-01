#ifndef __FRIENDSLIST_H
#define __FRIENDSLIST_H

#include "Node.h"

namespace DuiLib
{
struct tagFriendsInfo {
    bool m_bIsFolder;
    bool m_bIsEmpty;
    int m_iType; // 1-��ͨ��ϵ�� 2-���ں� 3-���ĺ�
    STLString m_strID;
    STLString m_strIDIco;
    STLString m_strName;
    STLString m_strTime;
    STLString m_strMessage;
    STLString m_strSoundIco;
};

class CFriendsListUI : public CListUI
{
public:
    enum {SCROLL_TIMERID = 10};

    CFriendsListUI(CPaintManagerUI *pclPaintManager);
    ~CFriendsListUI();

    bool Add(CControlUI *pclControl);
    bool AddAt(CControlUI *pclControl, int iIndex);

    bool Remove(CControlUI *pclControl);
    bool RemoveAt(int iIndex);
    void RemoveAll();

    void DoEvent(TEventUI &event);

    CNode *GetRoot();
    CNode *AddNode(const tagFriendsInfo &stItem, CNode *pclParent = NULL);
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

#endif // __FRIENDSLIST_H