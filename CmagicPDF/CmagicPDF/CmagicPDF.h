
// CmagicPDF.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCmagicPDFApp:
// �йش����ʵ�֣������ CmagicPDF.cpp
//

class CCmagicPDFApp : public CWinApp
{
public:
	CCmagicPDFApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCmagicPDFApp theApp;