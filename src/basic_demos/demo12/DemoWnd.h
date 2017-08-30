/*******************************************************************************
//标准窗口类  及使用方法     仅使用与  该版本的duilib中的  WindowImplBase 有些差异 可自行解决

//调用方法

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
									_In_opt_ HINSTANCE hPrevInstance,
									_In_ LPTSTR    lpCmdLine,
									_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HRESULT Hr = ::CoInitialize(NULL);//com调用 初始化
	::OleInitialize(NULL);//ole调用初始化
	if( FAILED(Hr) ) return 0;

	CPaintManagerUI::SetInstance(hInstance);
	CMainWnd* pFrame = new CMainWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("密级标志"), UI_WNDSTYLE_FRAME, 0 , 0, 0, 500, 300);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);
	pFrame->ShowModal();
	delete pFrame;
	pFrame = NULL;

	::CoUninitialize();
	::OleUninitialize();


	return 0;
}
********************************************************************************/


#pragma once

class CMainWnd : public WindowImplBase
{
public:
	CMainWnd(void);
	~CMainWnd(void);

	LPCTSTR GetWindowClassName() const;	
	virtual void InitWindow();
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	CControlUI* CreateControl(LPCTSTR pstrClass);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	bool IsNcLBMax();
	
	DUI_DECLARE_MESSAGE_MAP()
	void OnClick(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);	
	void OnItemSelect(TNotifyUI& msg);
public:
	void OnShowStatus();
public:
	CFileListUI* m_pFileList;
	CLabelUI* m_pStatusLab;
};

