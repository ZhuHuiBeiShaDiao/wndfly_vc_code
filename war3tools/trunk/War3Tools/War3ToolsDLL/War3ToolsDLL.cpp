// War3ToolsDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "War3ToolsDLL.h"


// ���ǵ���������һ��ʾ��
//WAR3TOOLSDLL_API int nWar3ToolsDLL=0;

// ���ǵ���������һ��ʾ����
//WAR3TOOLSDLL_API int fnWar3ToolsDLL(void)
//{
//	return 42;
//}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� War3ToolsDLL.h
//CWar3ToolsDLL::CWar3ToolsDLL()
//{
//	return;
//}

HKEY hRoot = HKEY_CURRENT_USER;
LPCWSTR lpSubKey = L"Software\\War3Tools";
DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
DWORD dwType = REG_SZ;

//��ȡע����ֵ
WAR3TOOLSDLL_API BOOL ReadReg(LPCWSTR lpRegKeyName, LPWSTR lpValue)
{
	HKEY hKey;

	LONG lRet = ::RegCreateKeyEx(hRoot,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	
	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
		return FALSE;
	}

	// ��ȡע����ֵ������
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

//д��ע����ֵ
WAR3TOOLSDLL_API BOOL WriteReg(LPCWSTR lpRegKeyName, LPCWSTR lpValue)
{
	HKEY hKey;
	DWORD dwSize = sizeof(lpValue);

	LONG lRet = ::RegCreateKeyEx(hRoot,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	
	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	// ����ע����ֵ������
	lRet = ::RegSetKeyValue(hKey,NULL,lpRegKeyName,dwType,(LPCVOID)lpValue,dwSize);

	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	::RegCloseKey(hKey);

	return TRUE;
}

//ɾ��ע����ֵ
WAR3TOOLSDLL_API BOOL DelReg(LPCWSTR lpRegKeyName)
{
	HKEY hKey;

	LONG lRet = ::RegCreateKeyEx(hRoot,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	
	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}
	
	// ɾ��ע����ֵ
	lRet = ::RegDeleteValue(hKey,lpRegKeyName);

	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	::RegCloseKey(hKey);

	return TRUE;
}