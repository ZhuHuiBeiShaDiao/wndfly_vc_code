// delpps.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

BOOL DelFile();
BOOL DelReg();
BOOL ReMoveDir(LPWSTR pszDir);
BOOL ReMoveRegDir(LPCWSTR lpSubKey);

int _tmain(int argc, _TCHAR* argv[])
{
	::system("pause");
	printf("����ж��PPS...\n");
	DelFile();
	printf("�ļ�ɾ���ɹ�\n");
	DelReg();
	printf("ע�������ɹ�\n");
	::system("pause");

	return 0;
}

BOOL DelFile()
{
	// ���弸����Ҫ��Ŀ¼
	TCHAR szWindowsDir[MAX_PATH] = {};
	TCHAR szAppDataDir[MAX_PATH] = {};
	TCHAR szAllUserDir[MAX_PATH] = {};
	TCHAR szProgrmDir[MAX_PATH] = {};
	TCHAR szCurrentUserDir[MAX_PATH] = {};
	TCHAR szPpsDir[MAX_PATH] = {};

	// ��ϵͳ���������л�ȡ��ʵĿ¼
	::ExpandEnvironmentStrings(L"%windir%",szWindowsDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%APPDATA%",szAppDataDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%ALLUSERSPROFILE%",szAllUserDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%ProgramFiles%",szProgrmDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%HOMEPATH%",szCurrentUserDir,MAX_PATH);

	// ����ע�����
	HKEY hKey;
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	LPCWSTR lpSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream";
	LPCWSTR lpRegKeyName = L"SetupPath";
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	DWORD dwType = REG_SZ;

	// ��ע�����
	LONG lRet = ::RegOpenKeyEx(hRoot,lpSubKey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&hKey);

	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
	}
	
	// ��ȡע����ֵ������
	DWORD dwValue;
	::RegQueryValueEx(hKey,lpRegKeyName,NULL,&dwType,NULL,&dwValue);
	
	if(dwValue == 0)
	{
		wcscpy_s(szPpsDir,2,L"");
	}else{
		LPWSTR lpValueEx = new WCHAR[dwValue];
		::RegQueryValueEx(hKey,lpRegKeyName,NULL,&dwType,(LPBYTE)lpValueEx,&dwValue);
		wcscpy_s(szPpsDir,MAX_PATH,lpValueEx);
	}

	::RegCloseKey(hKey);

	// ǿ�ƽ���PPS����
	::system("taskkill /f /im PPSAP.exe");
	::system("taskkill /f /im PPStream.exe");

	LPWSTR lpValue = new WCHAR[MAX_PATH];

	// ɾ���ļ�
	::wcscpy_s(lpValue,MAX_PATH,szWindowsDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\powerplayer.ini");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szWindowsDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\psnetwork.ini");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szWindowsDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\Powerlist.ini");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szAllUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\����\\PPSӰ��.lnk");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szAllUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\����ʼ���˵�\\����\\PPS Ӱ��.lnk");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szAppDataDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\Microsoft\\Internet Explorer\\Quick Launch\\PPSӰ��.lnk");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szCurrentUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\����ʼ���˵�\\����\\����\\PPS.lnk");
	::DeleteFile(lpValue);

	// ɾ���ļ���
	::wcscpy_s(lpValue,MAX_PATH,szAllUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\����ʼ���˵�\\����\\PPStream");
	ReMoveDir(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szProgrmDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\PPSGame");
	ReMoveDir(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szAppDataDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\PPStream");
	ReMoveDir(lpValue);

	ReMoveDir(szPpsDir);

	return TRUE;
}

BOOL DelReg()
{
	ReMoveRegDir(L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream");
	ReMoveRegDir(L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPSGame");
	ReMoveRegDir(L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPS��Ϸ_is1");
	//::RegDeleteKeyW(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream");
	//::RegDeleteValue(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream");
	//::RegDeleteKeyEx(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPSGame",KEY_ALL_ACCESS,REG_OPTION_NON_VOLATILE);
	//::RegDeleteKeyEx(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPS��Ϸ_is1",KEY_ALL_ACCESS,REG_OPTION_NON_VOLATILE);
	return TRUE;
}

BOOL ReMoveDir(LPWSTR pszDir)
{
	::wcscat_s(pszDir,MAX_PATH,L"\0");
	::SHFILEOPSTRUCT fop;
	fop.hwnd = NULL;
	fop.wFunc = FO_DELETE;
	fop.pTo = NULL;
	fop.fFlags = FOF_SILENT|FOF_NOCONFIRMATION;
	fop.pFrom = pszDir;
	::SHFileOperation(&fop);
	return TRUE;
}

BOOL ReMoveRegDir(LPCWSTR lpSubKey)
{
	// ����ע�����
	HKEY hKey;
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	DWORD dwType = REG_SZ;

	// ��ע�����
	LONG lRet = ::RegOpenKeyEx(hRoot,lpSubKey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&hKey);

	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
	}
	
	::RegDeleteValue(hKey,L"");
	::RegDeleteKey(hKey,L"");
	::RegCloseKey(hKey);
	return TRUE;
}
