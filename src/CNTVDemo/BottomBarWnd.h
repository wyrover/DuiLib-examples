#pragma once

#include "VolumeWnd.h"
#include "VolumeTipWnd.h"
#include "VolumeBackgroundWnd.h"
#include "ScreenRatioWnd.h"

class CBottomBarWnd : public CWindowWnd, public INotifyUI
{
public:
    CBottomBarWnd();
    ~CBottomBarWnd();
public:
    LPCTSTR GetWindowClassName() const;
    UINT GetClassStyle() const;

    HWND Create(HWND hWndParent, LPCTSTR pcszName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

    void Init();
public:
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void OnPrepare();
    void OnFinalMessage(HWND hWnd);

    void Notify(TNotifyUI& msg);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    void CreateVolume();
    void CreateVolumeTip();
    void CreateVolumeBackground();
    void CreateScreenRatio();

    void OnVolume(bool bShow = true);
    void OnVolumeTip(bool bShow = true);
    void OnVolumeBackground(bool bShow = true);
    void OnScreenRatio(bool bShow = true);
private:
    CPaintManagerUI m_clPaintManager;

    CButtonUI *m_pclResolutionBtn;
    CButtonUI *m_pclLiteWndBtn;
    CButtonUI *m_pclEpisodeBtn;
    CButtonUI *m_pclHSoundBtn;
    CButtonUI *m_pclLSoundBtn;
    CButtonUI *m_pclMuteBtn;
    CButtonUI *m_pclFullScreenBtn;
    CButtonUI *m_pclNormalScreenBtn;

    CVolumeWnd *m_pclVolumeWnd;
    CVolumeTipWnd *m_pclVolumeTipWnd;
    CVolumeBackgroundWnd *m_pclVolumeBackgroundWnd;

    CScreenRatioWnd *m_pclScreenRatioWnd;

    HWND m_hParentWnd;
    CHAR m_szWParam[128];
    CHAR m_szLParam[128];
};

