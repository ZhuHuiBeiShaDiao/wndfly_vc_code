// HookSendTo.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "HookSendTo.h"


// ���ǵ���������һ��ʾ��
HOOKSENDTO_API int nHookSendTo=0;

// ���ǵ���������һ��ʾ����
HOOKSENDTO_API int fnHookSendTo(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� HookSendTo.h
CHookSendTo::CHookSendTo()
{
	return;
}
