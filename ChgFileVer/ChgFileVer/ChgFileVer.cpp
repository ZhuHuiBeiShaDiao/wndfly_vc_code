// ChgFileVer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define roundoffs(a, b, r)	(((LPBYTE)(b) - (LPBYTE)(a) + ((r)-1)) & ~((r)-1))
#define roundpos(b, a, r)	(((LPBYTE)(a)) + roundoffs(a,b,r))

BOOL ReadReg(HKEY hRoot,LPCWSTR lpSubKey, LPWSTR lpKeyValue, LPWSTR lpResult);
BOOL ReadVersion(LPCWSTR lpFileName, LPCWSTR lpStrInfo, LPWSTR lpResult);
BOOL WriteVersion(LPCWSTR lpFileName, LPCWSTR lpStrInfo, LPCWSTR lpSetInfo);
BOOL ReadVersionInfoAddr(LPCWSTR lpFileName, LPWSTR lpResult);

typedef struct tagVS_LANGANDCODEPAGE
{
	WORD wLanguage;
	WORD wCodePage;
}VS_LANGANDCODEPAGE;

typedef struct tagVS_VERSIONINFO 
{ 
    WORD wLength; 
    WORD wValueLength; 
    WORD wType; 
    WCHAR szKey[1]; 
    WORD wPadding1[1]; 
    VS_FIXEDFILEINFO Value;
    WORD wPadding2[1]; 
    WORD wChildren[1]; 
}VS_VERSIONINFO;

typedef struct tagVS_STRING{
  WORD  wLength;
  WORD  wValueLength;
  WORD  wType;
  WCHAR szKey[1];
  WORD  Padding[1];
  WORD  Value[1];
}VS_STRING;

typedef struct tagVS_STRINGTABLE{
  WORD wLength;
  WORD wValueLength;
  WORD wType;
  WCHAR szKey[1];
  WORD Padding[1];
  VS_STRING Children[1];
}VS_STRINGTABLE;

typedef struct tagVS_STRINGFILEINFO
{
  WORD wLength;
  WORD wValueLength;
  WORD wType;
  WCHAR szKey[1];
  WORD Padding[1];
  VS_STRINGTABLE Children[1];
}VS_STRINGFILEINFO;

typedef struct tagVS_VER
{ 
  WORD  wLength; 
  WORD  wValueLength; 
  WORD  wType; 
  WCHAR szKey[1]; 
  WORD  Padding[1]; 
  DWORD Value[1]; 
}VS_VER; 

typedef struct tagVS_VERFILEINFO
{ 
  WORD  wLength; 
  WORD  wValueLength; 
  WORD  wType; 
  WCHAR szKey[1]; 
  WORD  Padding[1]; 
  VS_VER   Children[1]; 
}VS_VERFILEINFO; 

int _tmain(int argc, _TCHAR* argv[])
{
	LPWSTR pszFileName = new WCHAR[MAX_PATH];
	//LPWSTR pszProVer = new WCHAR[MAX_PATH];
	//LPWSTR pszInfoAddr = new WCHAR[MAX_PATH];

	ReadReg(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\PPStream",L"SetupPath",pszFileName);

	::wcscat_s(pszFileName,MAX_PATH,L"\\PPStream.exe");

	//ReadVersion(pszFileName,L"ProductVersion",pszProVer);
	//ReadVesionInfoAddr(pszFileName, pszInfoAddr);
	WriteVersion(pszFileName, L"ProductVersion", L"99, 0, 0, 0");

	delete [] pszFileName;
	//delete [] pszInfoAddr;
	//delete [] pszProVer;
	//::CloseHandle(hUpdate);
	return 0;
}

BOOL WriteVersion(LPCWSTR lpFileName, LPCWSTR lpStrInfo, LPCWSTR lpSetInfo)
{
	HANDLE hUpdate;
	VS_LANGANDCODEPAGE* lpTranslate;
	VS_FIXEDFILEINFO* lpFixedFileInfo;
	VS_VERSIONINFO* lpVerInfo;
	VS_STRINGFILEINFO* lpStringFileInfo;
	VS_STRINGTABLE* lpStringTable;
	VS_STRING* lpString;
	VS_VERFILEINFO* lpVerFileInfo;
	VS_VER* lpVer;

	//LPWSTR lpBuf1 = new WCHAR[MAX_PATH];
	//LPWSTR lpBuf2 = new WCHAR[MAX_PATH];
	//LPWSTR lpBuf3 = new WCHAR[MAX_PATH];
	DWORD dwVerInfoSize,dwVerHandle;

	/*ReadVesionInfoAddr(lpFileName,lpBuf1);

	wsprintf(lpBuf1,L"%s\\%s",lpBuf1,lpStrInfo);
	::wcscpy_s(lpBuf2,MAX_PATH,L"\\StringFileInfo\\");
	::wcscat_s(lpBuf2,MAX_PATH,lpBuf1);	
	*/

	dwVerInfoSize = GetFileVersionInfoSize(lpFileName, &dwVerHandle);

	if (dwVerInfoSize)
	{
		LPBYTE lpBuffer = new BYTE[dwVerInfoSize];
		BOOL bRet = GetFileVersionInfo(lpFileName, dwVerHandle, dwVerInfoSize, lpBuffer);

		if(bRet == FALSE)
		{
			//delete [] lpBuf1;
			//delete [] lpBuf2;
			//delete [] lpBuf3;
			delete [] lpBuffer;
			return FALSE;
		}

		lpVerInfo = (VS_VERSIONINFO*)lpBuffer;
		LPBYTE lpBuf = (LPBYTE) &lpVerInfo->szKey[wcslen(lpVerInfo->szKey)+1];
		lpFixedFileInfo = (VS_FIXEDFILEINFO*)roundpos(lpBuf, lpVerInfo, 4);
		lpStringFileInfo = (VS_STRINGFILEINFO*)roundpos(((LPBYTE)lpFixedFileInfo) + lpVerInfo->wValueLength, lpFixedFileInfo, 4);

		for(; ((LPBYTE)lpStringFileInfo) < (((LPBYTE)lpVerInfo) + lpVerInfo->wLength); lpStringFileInfo = (VS_STRINGFILEINFO*)roundpos((((LPBYTE)lpStringFileInfo) + lpStringFileInfo->wLength), lpStringFileInfo, 4))
		{
			if(!wcscmp(lpStringFileInfo->szKey, L"StringFileInfo"))
			{
				lpStringTable = (VS_STRINGTABLE*)roundpos(&lpStringFileInfo->szKey[wcslen(lpStringFileInfo->szKey)+1], lpStringFileInfo, 4);
				for(; ((LPBYTE)lpStringTable) < (((LPBYTE)lpStringFileInfo) + lpStringFileInfo->wLength); lpStringTable = (VS_STRINGTABLE*)roundpos((((LPBYTE)lpStringTable) + lpStringTable->wLength), lpStringTable, 4))
				{
					lpString = (VS_STRING*)roundpos(&lpStringTable->szKey[wcslen(lpStringTable->szKey)+1], lpStringTable, 4);
					for(; ((LPBYTE)lpString) < (((LPBYTE)lpStringTable) + lpStringTable->wLength); lpString = (VS_STRING*)roundpos((((LPBYTE)lpString) + lpString->wLength), lpString, 4))
					{
						LPTSTR lpszVal = (LPTSTR)roundpos(&lpString->szKey[wcslen(lpString->szKey)+1], lpString, 4);
						if(!_wcsicmp(lpString->szKey, lpStrInfo))
						{
							::wcscpy_s(lpszVal, lpString->wValueLength, lpSetInfo);
							//printf("  %-18S: %.*S\n", lpString->szKey, lpString->wValueLength,lpszVal);
						}
					}
				}
			}else{
				lpVerFileInfo = (VS_VERFILEINFO*)lpStringFileInfo;
				lpVer = (VS_VER*)roundpos(&lpStringFileInfo->szKey[wcslen(lpStringFileInfo->szKey)+1], lpStringFileInfo, 4);
				for (; ((LPBYTE)lpVer) < (((LPBYTE)lpVerFileInfo) + lpVerFileInfo->wLength); lpVer = (VS_VER*)roundpos((((LPBYTE)lpVer) + lpVer->wLength), lpVer, 4))
				{
					//printf(" %S: ", pV->szKey);
					// Iterate through the array of pairs of 16-bit language ID values that make up the standard 'Translation' VarFileInfo element.
					lpTranslate = (VS_LANGANDCODEPAGE*)roundpos(&lpVer->szKey[wcslen(lpVer->szKey)+1], lpVer, 4);
					//for (WORD* wpos = pwV ; ((byte*) wpos) < (((byte*) pwV) + pV->wValueLength); wpos+=2) {
						//printf("%04x%04x ", (int)*wpos++, (int)(*(wpos+1)));
					//}
					//printf("\n");
				}
			}
		}

		hUpdate = ::BeginUpdateResource(lpFileName,FALSE);

		if(hUpdate == NULL)
		{
			//delete [] lpBuf1;
			//delete [] lpBuf2;
			//delete [] lpBuf3;
			::CloseHandle(hUpdate);
			delete [] lpBuffer;
			return FALSE;
		}

		::UpdateResource(hUpdate,RT_VERSION,MAKEINTRESOURCE(VS_VERSION_INFO),lpTranslate->wLanguage,lpBuffer,dwVerInfoSize);
		::EndUpdateResource(hUpdate,FALSE);

		/*bRet = ::VerQueryValue(lpBuffer, lpBuf2,(LPVOID*)&lpBuf3, &uInfoSize);

		if(bRet == FALSE)
		{
			delete [] lpBuf1;
			delete [] lpBuf2;
			delete [] lpBuf3;
			delete [] lpBuffer;
			return FALSE;
		}

		//::ZeroMemory(lpBuf3,MAX_PATH);
		::wcscpy_s(lpBuf3,MAX_PATH,lpSetInfo);*/

		delete [] lpBuffer;

	}

	//delete [] lpBuf1;
	//delete [] lpBuf2;
	//delete [] lpBuf3;
	//::CloseHandle(hUpdate);
	return TRUE;
}

//读产品信息段地址
BOOL ReadVersionInfoAddr(LPCWSTR lpFileName, LPWSTR lpResult)
{
	DWORD dwVerInfoSize,dwVerHandle;
	VS_LANGANDCODEPAGE *lpTranslate;

	dwVerInfoSize = GetFileVersionInfoSize(lpFileName, &dwVerHandle);

	if (dwVerInfoSize)
	{
		LPBYTE lpBuffer = new BYTE[dwVerInfoSize];
		UINT uInfoSize = 0;

		BOOL bRet = GetFileVersionInfo(lpFileName, dwVerHandle, dwVerInfoSize, lpBuffer);

		if(bRet == FALSE)
		{
			delete [] lpBuffer;
			return FALSE;
		}

		bRet = ::VerQueryValue(lpBuffer, L"\\VarFileInfo\\Translation",(LPVOID*)&lpTranslate, &uInfoSize);

		if(bRet == FALSE)
		{
			delete [] lpBuffer;
			return FALSE;
		}

		wsprintf(lpResult,L"%04x%04x",lpTranslate->wLanguage,lpTranslate->wCodePage);

		delete [] lpBuffer;

	}
	return TRUE;
}

//读产品版本号
BOOL ReadVersion(LPCWSTR lpFileName, LPCWSTR lpStrInfo, LPWSTR lpResult)
{
	LPWSTR lpBuf1 = new WCHAR[MAX_PATH];
	LPWSTR lpBuf2 = new WCHAR[MAX_PATH];
	LPWSTR lpBuf3 = new WCHAR[MAX_PATH];
	DWORD dwVerInfoSize,dwVerHandle;

	ReadVesionInfoAddr(lpFileName,lpBuf1);

	wsprintf(lpBuf1,L"%s\\%s",lpBuf1,lpStrInfo);
	::wcscpy_s(lpBuf2,MAX_PATH,L"\\StringFileInfo\\");
	::wcscat_s(lpBuf2,MAX_PATH,lpBuf1);	

	dwVerInfoSize = GetFileVersionInfoSize(lpFileName, &dwVerHandle);

	if (dwVerInfoSize)
	{
		LPBYTE lpBuffer = new BYTE[dwVerInfoSize];
		UINT uInfoSize = 0;

		BOOL bRet = GetFileVersionInfo(lpFileName, dwVerHandle, dwVerInfoSize, lpBuffer);

		if(bRet == FALSE)
		{
			delete [] lpBuf1;
			delete [] lpBuf2;
			delete [] lpBuf3;
			delete [] lpBuffer;
			return FALSE;
		}

		bRet = ::VerQueryValue(lpBuffer, lpBuf2,(LPVOID*)&lpBuf3, &uInfoSize);

		if(bRet == FALSE)
		{
			delete [] lpBuf1;
			delete [] lpBuf2;
			delete [] lpBuf3;
			delete [] lpBuffer;
			return FALSE;
		}

		::wcscpy_s(lpResult,MAX_PATH,lpBuf3);
		delete [] lpBuffer;

	}
	delete [] lpBuf1;
	delete [] lpBuf2;
	//delete [] lpBuf3;

	return TRUE;
}

//读取注册表键值
BOOL ReadReg(HKEY hRoot,LPCWSTR lpSubKey,LPWSTR lpKeyValue,LPWSTR lpResult)
{
	HKEY hKey;
	//HKEY hRoot = HKEY_LOCAL_MACHINE;
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	DWORD dwType = REG_SZ;

	// 打开注册表项
	LONG lRet = ::RegOpenKeyEx(hRoot,lpSubKey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&hKey);

	if(lRet != ERROR_SUCCESS)
	{
		::RegCloseKey(hKey);
		return FALSE;
	}

	// 读取注册表键值的内容
	DWORD dwValue;
	::RegQueryValueEx(hKey,lpKeyValue,NULL,&dwType,NULL,&dwValue);
	
	if(dwValue == 0)
	{
		wcscpy_s(lpResult,2,L"");
		::RegCloseKey(hKey);
		return FALSE;
	}

	LPWSTR lpValueEx = new WCHAR[dwValue];
	lRet = ::RegQueryValueEx(hKey,lpKeyValue,NULL,&dwType,(LPBYTE)lpValueEx,&dwValue);

	if(lRet != ERROR_SUCCESS)
	{
		wcscpy_s(lpResult,2,L"");
		::RegCloseKey(hKey);
		return FALSE;
	}
	::wcscpy_s(lpResult,MAX_PATH,lpValueEx);

	::RegCloseKey(hKey);
	delete [] lpValueEx;

	return TRUE;
}