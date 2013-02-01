// hookpps.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

BOOL DelFile(LPCWSTR lpFileName);

int _tmain(int argc, _TCHAR* argv[])
{
	// ������̬�⵼��������ԭ��
	typedef BOOL (*pStartHook)(VOID);
	typedef VOID (*pStopHook)(VOID);

	::printf("load dll ...\n");

	// ���ع��Ӷ�̬��
	HMODULE hModule = ::LoadLibraryA("HookSendTo.dll");
	if(hModule == NULL)
	{
		::printf("Load error");
	}else{
		::printf("load success \n");

		// ���屾�غ�������ȡ�ö�̬�⵼�������ĵ�ַ
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
					// ��װȫ��API����
					BOOL bRet = StartHook();
					if(bRet)
					{
						::printf("LoadHook success\n");
					}else{
						::printf("LoadHook error\n");
					}
					// ɾPPSVOD����
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
					// ж��ȫ��API����
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
				// ����Ϊ��.����Ŀ¼����Ŀ¼������Ϊ��..����Ŀ¼������һ��Ŀ¼
				if(findData.cFileName[0] == '.')
					continue;

				// �����Ŀ¼��ע�⣬��Ӧ�ö���������&������
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