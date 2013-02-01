// hookpps.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// ������̬�⵼��������ԭ��
	typedef BOOL (*pStartHook)(VOID);
	typedef VOID (*pStopHook)(VOID);

	::printf("load dll ...\n");

	// ���ع��Ӷ�̬��
	HMODULE hModule = ::LoadLibraryA("HookAPI2010.dll");
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

