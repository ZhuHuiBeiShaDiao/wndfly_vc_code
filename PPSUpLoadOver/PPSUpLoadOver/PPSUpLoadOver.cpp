// hookpps.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL DelFile(LPCWSTR lpFileName);

int _tmain(int argc, _TCHAR* argv[])
{
	// 声明动态库导出函数的原型
	typedef BOOL (*pStartHook)(VOID);
	typedef VOID (*pStopHook)(VOID);

	::printf("load dll ...\n");

	// 加载勾子动态库
	HMODULE hModule = ::LoadLibraryA("HookSendTo.dll");
	if(hModule == NULL)
	{
		::printf("Load error");
	}else{
		::printf("load success \n");

		// 定义本地函数，并取得动态库导出函数的地址
		pStartHook StartHook = (pStartHook)::GetProcAddress(hModule,"StartHook");
		pStopHook StopHook = (pStopHook)::GetProcAddress(hModule,"StopHook");

		::printf("please select:\n");
		::printf("1 - LoadHook;\n");
		::printf("2 - UnLoadHook;\n");
		int nTemp;
		while(true)
		{
			::scanf_s("%d",&nTemp);
			switch(nTemp)
			{
			case 1 : 
				{
					// 安装全局API勾子
					BOOL bRet = StartHook();
					if(bRet)
					{
						::printf("LoadHook success\n");
					}else{
						::printf("LoadHook error\n");
					}
					// 删PPSVOD缓存
					TCHAR szAppDataDir[MAX_PATH] = {};
					LPTSTR lpValue = new TCHAR[MAX_PATH];
					::ExpandEnvironmentStrings(L"%APPDATA%",szAppDataDir,MAX_PATH);
					::wcscpy_s(lpValue,MAX_PATH,szAppDataDir);
					::wcscat_s(lpValue,MAX_PATH,L"\\PPStream\\VodCache");
					DelFile(lpValue);
					break;
				}
			case 2:
				{
					// 卸载全局API勾子
					StopHook();
					::printf("UnLoadHook success\n");
					break;
				}
			default : ;
			}
		}
		//::printf("%d",nTemp);
	}

	::system("pause");
	::FreeLibrary(hModule);
	return 0;
}

BOOL DelFile(LPCWSTR lpFileName)
{
	DWORD dwRet = ::GetFileAttributes(lpFileName);
	if(dwRet == 0xFFFFFFFF)
	{
		return FALSE;
	}

	if(dwRet & FILE_ATTRIBUTE_DIRECTORY)
	{
		WIN32_FIND_DATA findData;
		HANDLE hFindFile;
		LPWSTR lpszDirName =  new WCHAR[MAX_PATH];
		LPWSTR lpszDirNameTemp = new WCHAR[MAX_PATH];
		::wcscpy_s(lpszDirName,MAX_PATH,lpFileName);
		::wcscat_s(lpszDirName,MAX_PATH,L"\\*.*");
		hFindFile = ::FindFirstFile(lpszDirName, &findData);
		if(hFindFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				// 名称为“.”的目录代表本目录，名称为“..”的目录代表上一层目录
				if(findData.cFileName[0] == '.')
					continue;

				// 如果是目录。注意，你应该对它们做“&”操作
				if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					::wcscpy_s(lpszDirNameTemp,MAX_PATH,lpFileName);
					::wcscat_s(lpszDirNameTemp,MAX_PATH,L"\\");
					::wcscat_s(lpszDirNameTemp,MAX_PATH,findData.cFileName);
					DelFile(lpszDirNameTemp);
				}else{
					//wprintf(L" %s \n", findData.cFileName);
					::wcscpy_s(lpszDirNameTemp,MAX_PATH,lpFileName);
					::wcscat_s(lpszDirNameTemp,MAX_PATH,L"\\");
					::wcscat_s(lpszDirNameTemp,MAX_PATH,findData.cFileName);
					::DeleteFile(lpszDirNameTemp);
				}

			}while(::FindNextFile(hFindFile, &findData));
			::FindClose(hFindFile);
		}
	}else{
		//wprintf(L" %s \n", lpFileName);
		::DeleteFile(lpFileName);
	}

	::RemoveDirectory(lpFileName);

	return TRUE;
}