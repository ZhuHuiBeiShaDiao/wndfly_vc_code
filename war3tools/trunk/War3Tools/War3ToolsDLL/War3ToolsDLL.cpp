// War3ToolsDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "War3ToolsDLL.h"


// 这是导出变量的一个示例
//WAR3TOOLSDLL_API int nWar3ToolsDLL=0;

// 这是导出函数的一个示例。
//WAR3TOOLSDLL_API int fnWar3ToolsDLL(void)
//{
//	return 42;
//}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 War3ToolsDLL.h
//CWar3ToolsDLL::CWar3ToolsDLL()
//{
//	return;
//}

HKEY hRoot = HKEY_CURRENT_USER;
LPCWSTR lpSubKey = L"Software\\War3Tools";
DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
DWORD dwType = REG_SZ;

//读取注册表键值
WAR3TOOLSDLL_API BOOL ReadReg(LPCWSTR lpRegKeyName, LPWSTR lpValue)
{
	HKEY hKey;

	LONG lRet = ::RegCreateKeyEx(hRoot,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	
	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
		return FALSE;
	}

	// 读取注册表键值的内容
	DWORD dwValue;
	::RegQueryValueEx(hKey,lpRegKeyName,NULL,&dwType,NULL,&dwValue);
	
	if(dwValue == 0)
	{
		wcscpy_s(lpValue,2,L"");
		::RegCloseKey(hKey);
		return FALSE;
	}

	LPWSTR lpValueEx = new WCHAR[dwValue];
	lRet = ::RegQueryValueEx(hKey,lpRegKeyName,NULL,&dwType,(LPBYTE)lpValueEx,&dwValue);
	wcscpy_s(lpValue,MAX_PATH,lpValueEx);

	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
		return FALSE;
	}

	::RegCloseKey(hKey);

	return TRUE;
}

//写入注册表键值
WAR3TOOLSDLL_API BOOL WriteReg(LPCWSTR lpRegKeyName, LPCWSTR lpValue)
{
	HKEY hKey;
	DWORD dwSize = sizeof(lpValue);

	LONG lRet = ::RegCreateKeyEx(hRoot,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	
	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	// 设置注册表键值的内容
	lRet = ::RegSetKeyValue(hKey,NULL,lpRegKeyName,dwType,(LPCVOID)lpValue,dwSize);

	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	::RegCloseKey(hKey);

	return TRUE;
}

//删除注册表键值
WAR3TOOLSDLL_API BOOL DelReg(LPCWSTR lpRegKeyName)
{
	HKEY hKey;

	LONG lRet = ::RegCreateKeyEx(hRoot,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	
	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}
	
	// 删除注册表键值
	lRet = ::RegDeleteValue(hKey,lpRegKeyName);

	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	::RegCloseKey(hKey);

	return TRUE;
}