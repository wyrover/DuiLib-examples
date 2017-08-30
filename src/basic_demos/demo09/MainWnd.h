#pragma once
#include <exdisp.h>
#include <comdef.h>

class CMainWndDlg : public WindowImplBase, public CWebBrowserEventHandler
{
public:
	CMainWndDlg(void);
	~CMainWndDlg(void);

public:
	LPCTSTR GetWindowClassName() const;	

	virtual CDuiString GetSkinFile();

	virtual CDuiString GetSkinFolder();

	virtual void OnFinalMessage(HWND hWnd);

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual void InitWindow();

	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void Notify(TNotifyUI& msg);

protected:	
	void WindowDataInit();

	void OnLBtnClick(CControlUI *pControl);

private:
	CButtonUI* m_pCloseBtn;		
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;

	CProgressUI* m_pProgress;	// 进度条控件

	CListUI* m_pList;			// List控件
};
