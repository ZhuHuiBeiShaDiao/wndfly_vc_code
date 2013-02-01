// RandomIP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

bool RandomIP(char* lpszIPAddr);

int _tmain(int argc, _TCHAR* argv[])
{
	char szIP[16] = {0};
	while(1)
	{
		RandomIP(szIP);
		printf("%s",szIP);
		getchar();
	}
	return 0;
}

bool RandomIP(char* lpszIPAddr)
{
	bool bFlag = true;
	while(bFlag)
	{
		bFlag = false;
		srand((unsigned)GetTickCount());

		int nIPa = ::rand() % 255;
		int nIPb = ::rand() % 255;
		int nIPc = ::rand() % 255;
		int nIPd = ::rand() % 255;

		if(nIPa == 0 || nIPa == 10|| nIPd == 0)
		{
			bFlag = true;
		}
		if(nIPa == 172 && nIPb >= 16 && nIPb <= 30)
		{
			bFlag = true;
		}
		if(nIPa == 192 && nIPb == 168)
		{
			bFlag = true;
		}
		if(nIPa == 127 && nIPb == 0 && nIPc == 0 && nIPd == 1)
		{
			bFlag = true;
		}
		if(bFlag == false)
		{
			::sprintf(lpszIPAddr,"%d.%d.%d.%d\n",nIPa,nIPb,nIPc,nIPd);
		}
	}
	return true;
}