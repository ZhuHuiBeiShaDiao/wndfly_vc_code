// HookAPI2010.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HookAPI2010.h"


// 这是导出变量的一个示例
HOOKAPI2010_API int nHookAPI2010=0;

// 这是导出函数的一个示例。
HOOKAPI2010_API int fnHookAPI2010(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 HookAPI2010.h
CHookAPI2010::CHookAPI2010()
{
	return;
}
