// EditResource.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct VS_VERSIONINFO 
{ 
        WORD wLength; 
        WORD wValueLength; 
        WORD wType; 
        WCHAR szKey[1]; 
        WORD wPadding1[1]; 
        VS_FIXEDFILEINFO Value; 
        WORD wPadding2[1]; 
        WORD wChildren[1]; 
}; 

struct TRANSLATE
{ 
        WORD wLanguage; 
        WORD wCodePage; 
}*lpTranslate; 

typedef struct 
{
  WORD        wLength;
  WORD        wValueLength;
  WORD        wType;
  WCHAR       szKey;
  WORD        Padding;
  StringTable Children;
} StringFileInfo;


#define roundoffs(a,b,r) (((BYTE*)(b) - (BYTE*)(a) + ((r) - 1)) & ~((r) - 1)) 
#define roundpos(a,b,r) (((BYTE*)(a)) + roundoffs(a,b,r))

int _tmain(int argc, _TCHAR* argv[])
{
	VS_VERSIONINFO *pVerInfo; 
	LPBYTE pOffsetBytes; 
	VS_FIXEDFILEINFO *pFixedInfo; 
	LPCTSTR lpszFile = _T("D:\\test\\PPStream.exe"); 
	DWORD dwHandle,	dwSize, dwResult = 0; 

	dwSize = GetFileVersionInfoSize(lpszFile, &dwHandle); 

	if(0 < dwSize) 
	{ 
		LPBYTE lpBuffer = new BYTE[dwSize]; 
		BOOL bRet = ::GetFileVersionInfo(lpszFile,0, dwSize, lpBuffer);

		if(bRet) 
		{ 
			pVerInfo = (VS_VERSIONINFO*)lpBuffer; 
			pOffsetBytes = (BYTE*)&pVerInfo->szKey[_tcslen(pVerInfo->szKey) + 1]; 
			StringFileInfo->
			pFixedInfo = (VS_FIXEDFILEINFO*)roundpos(pVerInfo, pOffsetBytes, 4); 

			pFixedInfo->dwFileVersionMS = 0xFFFFFFFF; 
			pFixedInfo->dwFileVersionLS = 0xFFFFFFFF; 
			pFixedInfo->dwProductVersionMS = 252; 
			pFixedInfo->dwProductVersionLS = 585;

			HANDLE hResource = BeginUpdateResource(lpszFile, FALSE);

			if(hResource) 
			{ 
				UINT uTemp; 

				bRet = VerQueryValue(lpBuffer, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &uTemp);
				if(bRet)
				{ 
					bRet = UpdateResource(hResource, RT_VERSION, MAKEINTRESOURCE(VS_VERSION_INFO), lpTranslate->wLanguage, lpBuffer, dwSize);
					if(bRet)
					{ 
						bRet = EndUpdateResource(hResource, FALSE);
						if(!bRet)
						{
							dwResult = GetLastError(); 
						}
					} 
					else{ 
						dwResult = GetLastError(); 
					}
				} 
			} 
			else{ 
				dwResult = GetLastError();
			}
		} 
		else{ 
			dwResult = GetLastError(); 
		}

		delete [] lpBuffer; 
	} 
	else{
		dwResult = GetLastError();
	}

	if(dwResult != 0)
	{
		wprintf(_T( "Operation   was   not   successful.     Result   =   %lu\n "), dwResult);
	}
	::system("pause");
	return 0;
}
