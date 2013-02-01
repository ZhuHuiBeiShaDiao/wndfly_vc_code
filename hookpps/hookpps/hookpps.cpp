// hookpps.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 声明动态库导出函数的原型
	typedef BOOL (*pStartHook)(VOID);
	typedef VOID (*pStopHook)(VOID);

	::printf("load dll ...\n");

	// 加载勾子动态库
	HMODULE hModule = ::LoadLibraryA("HookAPI2010.dll");
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

