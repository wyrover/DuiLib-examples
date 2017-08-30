#include "StdAfx.h"
#include "DemoWnd.h"

//

DUI_BEGIN_MESSAGE_MAP(CMainWnd, WindowImplBase)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMSELECT, OnItemSelect)
DUI_END_MESSAGE_MAP()

CMainWnd::CMainWnd(void)
	: m_pFileList(NULL)
{
}


CMainWnd::~CMainWnd(void)
{
}

LPCTSTR CMainWnd::GetWindowClassName() const
{
	return _T("UIDemoFrame");//类名
}

DuiLib::CDuiString CMainWnd::GetSkinFile()
{
	return _T("skin.xml");//设置的xml路径
}

DuiLib::CDuiString CMainWnd::GetSkinFolder()
{
	return _T("skin\\");//设置的资源路径
}

CControlUI* CMainWnd::CreateControl( LPCTSTR pstrClass )
{
	
	return NULL;//添加系统除外的自定义控件
}

LRESULT CMainWnd::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;//处理自定义的消息
}

bool CMainWnd::IsNcLBMax()
{
	return false;//是否双击最大化  
}

void CMainWnd::InitWindow()
{
	//获取控件的指针 如果需要的话  这时  对话框还没有显示
	m_pFileList = static_cast<CFileListUI*>(m_PaintManager.FindControl(_T("file_list")));
	m_pStatusLab = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("status_lab")));
}

void CMainWnd::OnPrepare( TNotifyUI& msg )
{
	//对话框开始绘制 对话框初始化函数 
	CDuiString sTemp;
	for (int i=0; i<100; i++)
	{
		CFileListItemUI* pListItem = new CFileListItemUI;
		pListItem->SetFileList(m_pFileList);//必须在前面设置FileList  后面有些函数需要
		pListItem->SetFixedHeight(24);
				
		//第一列
		CHorizontalLayoutUI* pHor = new CHorizontalLayoutUI;
		CCheckBoxUI* pCheck = new CCheckBoxUI;
		RECT paddingRect = {0};
		int nPadding = (24 - 16)/2;
		paddingRect.left = paddingRect.top = paddingRect.bottom = nPadding;
		paddingRect.right =0;
		//pCheck->SetPadding(paddingRect);
		pCheck->SetFixedWidth(30);
		pCheck->SetAttribute(_T("align"),_T("center"));
		pCheck->SetNormalImage(_T("file='checkbox_h.png' dest='10,4,27,21'"));//17图片好看些
		pCheck->SetSelectedImage(_T("file='checkbox_ph.png' dest='10,4,27,21'"));
		pHor->Add(pCheck);
		pListItem->SetCheckEvent(pCheck);

			
		CPictureUI *pPicture = new CPictureUI;//自定义图片控件
		pPicture->SetPadding(paddingRect);
		pPicture->SetFixedWidth(17);//17图片好看些
		pPicture->SetAttribute(_T("align"),_T("center"));
		pPicture->SetAttribute(_T("valign"), _T("center"));
		pPicture->SetBkImage(_T("doc_32.gif"));
		pHor->Add(pPicture);

		sTemp.Format(_T("新建文档文件 %2d.doc"), i);
		CLabelUI* pLabel = new CLabelUI;
		pLabel->SetName(LABEL_FILENAME);//方便 后面重命名 取值
		pLabel->SetText(sTemp);
		pLabel->SetAttribute(_T("padding"), _T("5,0,0,0"));
		pLabel->SetToolTip(sTemp);
		pLabel->SetEndellipsis(true);
		pLabel->SetShowHtml(true);
		pHor->Add(pLabel);
		pListItem->Add(pHor);
	
		/*pListItem->m_pButton = new CButtonUI;
		pListItem->m_pButton->SetText(_T("删除"));
		pListItem->m_pButton->SetVisible(false);
		pListItem->m_pButton->SetFixedWidth(20);
		pListItem->Add(pListItem->m_pButton, 0);*/

		//第二列
		sTemp.Format(_T(" %2d K"), i*10);
		pLabel = new CLabelUI;
		pLabel->SetText(sTemp);
		pLabel->SetAttribute(_T("padding"), _T("5,0,0,0"));
		pListItem->Add(pLabel);

		//第三列
		sTemp.Format(_T("2015-05-07 %2d:%2d:%2d"), rand() % 24, rand() % 60, rand() % 60);
		pLabel = new CLabelUI;
		pLabel->SetText(sTemp);
		pLabel->SetAttribute(_T("padding"), _T("5,0,0,0"));
		pListItem->Add(pLabel);

		
		m_pFileList->Add(pListItem);
	}
}

void CMainWnd::OnClick( TNotifyUI& msg )
{
	if(msg.pSender == m_pFileList)
	{
		OnShowStatus();
		return ;
	}
	WindowImplBase::OnClick(msg);
}

void CMainWnd::OnItemSelect( TNotifyUI& msg )
{
	if(msg.pSender == m_pFileList)
	{
		OnShowStatus();//
		return ;
	}
}

void CMainWnd::OnShowStatus()
{
	int nSelectCount = m_pFileList->GetSelectCount();
	if(nSelectCount > 0)
	{
		CDuiString str;
		str.Format(_T("已选中%d个文件/文件夹"), nSelectCount);
		m_pStatusLab->SetText(str);
	}
	else
	{
		CDuiString str;
		str.Format(_T("%d项"), m_pFileList->GetCount());
		m_pStatusLab->SetText(str);
	}
}


