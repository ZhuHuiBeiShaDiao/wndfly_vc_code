// delpps.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL DelFile();
BOOL DelReg();
BOOL ReMoveDir(LPWSTR pszDir);
BOOL ReMoveRegDir(LPCWSTR lpSubKey);

int _tmain(int argc, _TCHAR* argv[])
{
	::system("pause");
	printf("正在卸载PPS...\n");
	DelFile();
	printf("文件删除成功\n");
	DelReg();
	printf("注册表清理成功\n");
	::system("pause");

	return 0;
}

BOOL DelFile()
{
	// 定义几个主要的目录
	TCHAR szWindowsDir[MAX_PATH] = {};
	TCHAR szAppDataDir[MAX_PATH] = {};
	TCHAR szAllUserDir[MAX_PATH] = {};
	TCHAR szProgrmDir[MAX_PATH] = {};
	TCHAR szCurrentUserDir[MAX_PATH] = {};
	TCHAR szPpsDir[MAX_PATH] = {};

	// 从系统环境变量中获取真实目录
	::ExpandEnvironmentStrings(L"%windir%",szWindowsDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%APPDATA%",szAppDataDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%ALLUSERSPROFILE%",szAllUserDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%ProgramFiles%",szProgrmDir,MAX_PATH);
	::ExpandEnvironmentStrings(L"%HOMEPATH%",szCurrentUserDir,MAX_PATH);

	// 定义注册表相
	HKEY hKey;
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	LPCWSTR lpSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream";
	LPCWSTR lpRegKeyName = L"SetupPath";
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	DWORD dwType = REG_SZ;

	// 打开注册表项
	LONG lRet = ::RegOpenKeyEx(hRoot,lpSubKey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&hKey);

	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
	}
	
	// 读取注册表键值的内容
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

	// 强制结束PPS进程
	::system("taskkill /f /im PPSAP.exe");
	::system("taskkill /f /im PPStream.exe");

	LPWSTR lpValue = new WCHAR[MAX_PATH];

	// 删除文件
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
	::wcscat_s(lpValue,MAX_PATH,L"\\桌面\\PPS影音.lnk");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szAllUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\「开始」菜单\\程序\\PPS 影音.lnk");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szAppDataDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\Microsoft\\Internet Explorer\\Quick Launch\\PPS影音.lnk");
	::DeleteFile(lpValue);

	::wcscpy_s(lpValue,MAX_PATH,szCurrentUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\「开始」菜单\\程序\\启动\\PPS.lnk");
	::DeleteFile(lpValue);

	// 删除文件夹
	::wcscpy_s(lpValue,MAX_PATH,szAllUserDir);
	::wcscat_s(lpValue,MAX_PATH,L"\\「开始」菜单\\程序\\PPStream");
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
	ReMoveRegDir(L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPS游戏_is1");
	//::RegDeleteKeyW(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream");
	//::RegDeleteValue(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream");
	//::RegDeleteKeyEx(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPSGame",KEY_ALL_ACCESS,REG_OPTION_NON_VOLATILE);
	//::RegDeleteKeyEx(HKEY_LOCAL_MACHINE,L"\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPS游戏_is1",KEY_ALL_ACCESS,REG_OPTION_NON_VOLATILE);
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
	// 定义注册表相
	HKEY hKey;
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	DWORD dwType = REG_SZ;

	// 打开注册表项
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
