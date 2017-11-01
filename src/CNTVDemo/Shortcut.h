#pragma once

class CShortcut
{
public:
    CShortcut();
    ~CShortcut();
public:
    static bool GetModule(LPTSTR pszModulePath, int iModuleLen, LPTSTR pszExeName, int iExeLen);
    static bool GetLinkPath(LPTSTR pszBuffer, int iBufferLen);
    static bool CreateLink(LPCTSTR lpcszPath, LPCTSTR lpcszDescription, int iShowCmd = SW_SHOWNORMAL);
};

