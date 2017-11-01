#ifndef __NODE_H
#define __NODE_H

#include <math.h>

namespace DuiLib
{

struct tagNodeData {
    int m_iLevel;
    bool m_bIsFolder;
    bool m_bChildVisible;
    bool m_bHasChild;
    int m_iType;
    STLString m_strText;
    STLString m_strValue;
    CListContainerElementUI *m_pclListElement;
};

double CalculateDelay(double state);

class CNode
{
public:
    CNode();
    explicit CNode(tagNodeData &stNodeData);
    CNode(tagNodeData &stNodeData, CNode *pclParent);
    ~CNode();

    tagNodeData &GetData();

    int GetChildrenCount() const;

    CNode *GetChild(int i);
    CNode *GetParent();

    bool IsFolder() const;
    bool HasChild() const;

    void AddChild(CNode *pclChild);
    void RemoveChild(CNode *pclChild);

    CNode *GetLastChild();
private:
    void SetParent(CNode *pclParent);
private:
    typedef std::vector<CNode *> Children;

    Children m_clChildren;
    CNode *m_pclParent;

    tagNodeData m_stNodeData;
};

} // DuiLib

#endif