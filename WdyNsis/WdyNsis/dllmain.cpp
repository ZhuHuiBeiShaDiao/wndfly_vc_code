// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "WdyNsis.h"

HINSTANCE g_hInstance;

HWND g_hwndParent;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hInstance = hModule;
		return TRUE;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

WDYNSIS_API BOOL WriteVersion(HWND hwndParent, int string_size, char *variables, stack_t **stacktop, extra_parameters *extra)
{
	g_hwndParent=hwndParent;

	EXDLL_INIT();

	char lpFileNameA[MAX_PATH] = {0};
	char lpStrInfoA[MAX_PATH] = {0};
	char lpSetInfoA[MAX_PATH] = {0};

	popstring(lpFileNameA);
	popstring(lpStrInfoA);
	popstring(lpSetInfoA);

	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, lpFileNameA, -1, NULL, 0);
	LPTSTR lpFileName = new TCHAR[dwNum];
	MultiByteToWideChar (CP_ACP, 0, lpFileNameA, -1, lpFileName, dwNum);

	dwNum = MultiByteToWideChar (CP_ACP, 0, lpStrInfoA, -1, NULL, 0);
	LPTSTR lpStrInfo = new TCHAR[dwNum];
	MultiByteToWideChar (CP_ACP, 0, lpStrInfoA, -1, lpStrInfo, dwNum);

	dwNum = MultiByteToWideChar (CP_ACP, 0, lpSetInfoA, -1, NULL, 0);
	LPTSTR lpSetInfo = new TCHAR[dwNum];
	MultiByteToWideChar (CP_ACP, 0, lpSetInfoA, -1, lpSetInfo, dwNum);

	HANDLE hUpdate;
	VS_LANGANDCODEPAGE* lpTranslate;
	VS_FIXEDFILEINFO* lpFixedFileInfo;
	VS_VERSIONINFO* lpVerInfo;
	VS_STRINGFILEINFO* lpStringFileInfo;
	VS_STRINGTABLE* lpStringTable;
	VS_STRING* lpString;
	VS_VERFILEINFO* lpVerFileInfo;
	VS_VER* lpVer;

	DWORD dwVerInfoSize,dwVerHandle;

	dwVerInfoSize = GetFileVersionInfoSize(lpFileName, &dwVerHandle);

	if (dwVerInfoSize)
	{
		LPBYTE lpBuffer = new BYTE[dwVerInfoSize];
		BOOL bRet = GetFileVersionInfo(lpFileName, dwVerHandle, dwVerInfoSize, lpBuffer);

		if(bRet == FALSE)
		{
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
						}
					}
				}
			}else{
				lpVerFileInfo = (VS_VERFILEINFO*)lpStringFileInfo;
				lpVer = (VS_VER*)roundpos(&lpStringFileInfo->szKey[wcslen(lpStringFileInfo->szKey)+1], lpStringFileInfo, 4);
				for (; ((LPBYTE)lpVer) < (((LPBYTE)lpVerFileInfo) + lpVerFileInfo->wLength); lpVer = (VS_VER*)roundpos((((LPBYTE)lpVer) + lpVer->wLength), lpVer, 4))
				{
					lpTranslate = (VS_LANGANDCODEPAGE*)roundpos(&lpVer->szKey[wcslen(lpVer->szKey)+1], lpVer, 4);
				}
			}
		}

		hUpdate = ::BeginUpdateResource(lpFileName,FALSE);

		if(hUpdate == NULL)
		{
			::CloseHandle(hUpdate);
			delete [] lpBuffer;
			return FALSE;
		}

		::UpdateResource(hUpdate,RT_VERSION,MAKEINTRESOURCE(VS_VERSION_INFO),lpTranslate->wLanguage,lpBuffer,dwVerInfoSize);
		::EndUpdateResource(hUpdate,FALSE);

		delete [] lpBuffer;

	}

	return TRUE;
}