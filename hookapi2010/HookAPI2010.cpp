// HookAPI2010.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "HookAPI2010.h"


// ���ǵ���������һ��ʾ��
HOOKAPI2010_API int nHookAPI2010=0;

// ���ǵ���������һ��ʾ����
HOOKAPI2010_API int fnHookAPI2010(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� HookAPI2010.h
CHookAPI2010::CHookAPI2010()
{
	return;
}
