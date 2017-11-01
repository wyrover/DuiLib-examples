#include "stdafx.h"
#include "Shortcut.h"
#include <stdio.h>
#include <string>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib")

CShortcut::CShortcut()
{
}


CShortcut::~CShortcut()
{
}

bool CShortcut::GetLinkPath(LPTSTR pszBuffer, int iBufferLen)
{
    if ((pszBuffer == NULL) || (iBufferLen <= 0)) {
        return false;
    }

    LPITEMIDLIST ppIdList = NULL;
    HRESULT lResult = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOPDIRECTORY, &ppIdList);

    if (lResult != S_OK) {
        return false;
    }

    BOOL bResult = SHGetPathFromIDList(ppIdList, pszBuffer);
    CoTaskMemFree(ppIdList);
    ppIdList = NULL;
    return (bResult ? true : false);
}

bool CShortcut::GetModule(LPTSTR pszModulePath, int iModuleLen, LPTSTR pszExeName, int iExeLen)
{
    if ((pszModulePath == NULL) || (wcslen(pszModulePath) == 0) || (iModuleLen <= 0)
        || (pszExeName == NULL) || (wcslen(pszExeName) == 0) || (iExeLen <= 0)) {
        return false;
    }

    WCHAR szTemp[MAX_PATH] = { 0 };
    WCHAR szPath[MAX_PATH] = { 0 };
    bool bResult = false;
    GetModuleFileName(NULL, szTemp, sizeof(szTemp));
    LPTSTR pszTemp = _tcsrchr(szTemp, L'\\');

    if (pszTemp != NULL) {
        _snwprintf_s(pszExeName, iExeLen, _TRUNCATE, L"%s", pszTemp + 1);
        *pszTemp = '\0';
        _snwprintf_s(pszModulePath, iModuleLen, _TRUNCATE, L"%s", pszTemp);
        bResult = true;
    }

    return bResult;
}

bool CShortcut::CreateLink(LPCTSTR lpcszLinkPath, LPCTSTR lpcszDescription, int iShowCmd)
{
    if ((lpcszLinkPath == NULL) || (wcslen(lpcszLinkPath) == 0)
        || (lpcszDescription == NULL) || (wcslen(lpcszDescription) == 0)) {
        return false;
    }

    IShellLink *pLink = NULL;
    HRESULT lResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);

    if (FAILED(lResult)) {
        return false;
    }

    IPersistFile *ppFile = NULL;
    lResult = pLink->QueryInterface(IID_IPersistFile, (void **)&ppFile);

    if (FAILED(lResult)) {
        pLink->Release();
        return false;
    }

    pLink->SetDescription(lpcszDescription);
    pLink->SetShowCmd(iShowCmd);
    WCHAR szTemp[MAX_PATH] = { 0 };
    WCHAR szPath[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, szPath, sizeof(szPath));
    // 可执行程序的完整路径
    pLink->SetPath(szPath);
    LPTSTR pszTemp = _tcsrchr(szPath, L'\\');

    if (pszTemp == NULL) {
        ppFile->Release();
        pLink->Release();
        return false;
    }

    *pszTemp = L'\0';
    // 可执行程序所在目录
    pLink->SetWorkingDirectory(szPath);
    _snwprintf_s(szTemp, sizeof(szTemp), _TRUNCATE, L"%s", pszTemp + 1);
    pszTemp = _tcsrchr(szTemp, L'.');

    if (pszTemp == NULL) {
        ppFile->Release();
        pLink->Release();
        return false;
    }

    *pszTemp = '\0';
    // 快捷方式完整路径
    _snwprintf_s(szPath, sizeof(szPath), _TRUNCATE, L"%s\\%s%s", lpcszLinkPath, szTemp, L".lnk");
    lResult = ppFile->Save(szPath, TRUE);
    ppFile->Release();
    pLink->Release();
    return SUCCEEDED(lResult);
}