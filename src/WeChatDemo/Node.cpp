#include "stdafx.h"
#include "Node.h"

namespace DuiLib
{

double CalculateDelay(double dState)
{
    return pow(dState, 2);
}

CNode::CNode() : m_pclParent(NULL)
{
}

CNode::CNode(tagNodeData &stNodeData)
    : m_stNodeData(stNodeData), m_pclParent(NULL)
{
}

CNode::CNode(tagNodeData &stNodeData, CNode *pclParent)
    : m_stNodeData(stNodeData), m_pclParent(pclParent)
{
}

CNode::~CNode()
{
    for (int i = 0; i < GetChildrenCount(); ++i) {
        if (m_clChildren[i] != NULL) {
            delete m_clChildren[i];
            m_clChildren[i] = NULL;
        }
    }
}

void CNode::SetParent(CNode *pclParent)
{
    m_pclParent = pclParent;
}

tagNodeData & CNode::GetData()
{
    return m_stNodeData;
}

int CNode::GetChildrenCount() const
{
    return static_cast<int>(m_clChildren.size());
}

CNode *CNode::GetChild(int i)
{
    return m_clChildren[i];
}

CNode *CNode::GetParent()
{
    return m_pclParent;
}

bool CNode::HasChild() const
{
    return GetChildrenCount() > 0;
}

bool CNode::IsFolder() const
{
    return m_stNodeData.m_bIsFolder;
}

void CNode::AddChild(CNode *pclChild)
{
    pclChild->SetParent(this);
    m_clChildren.push_back(pclChild);
}

void CNode::RemoveChild(CNode *pclChild)
{
    Children::iterator pIter = m_clChildren.begin();

    for (; pIter < m_clChildren.end(); ++pIter) {
        if (*pIter == pclChild) {
            m_clChildren.erase(pIter);
            return;
        }
    }
}

CNode *CNode::GetLastChild()
{
    if (HasChild()) {
        return GetChild(GetChildrenCount() - 1)->GetLastChild();
    }

    return this;
}

} // namespace DuiLib