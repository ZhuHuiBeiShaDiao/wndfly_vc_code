// DelFileDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "DelFileDll.h"


// ���ǵ���������һ��ʾ��
DELFILEDLL_API int nDelFileDll=0;

// ���ǵ���������һ��ʾ����
DELFILEDLL_API int fnDelFileDll(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� DelFileDll.h
CDelFileDll::CDelFileDll()
{
	return;
}