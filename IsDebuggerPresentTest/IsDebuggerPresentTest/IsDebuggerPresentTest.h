
// IsDebuggerPresentTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIsDebuggerPresentTestApp:
// �йش����ʵ�֣������ IsDebuggerPresentTest.cpp
//

class CIsDebuggerPresentTestApp : public CWinApp
{
public:
	CIsDebuggerPresentTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIsDebuggerPresentTestApp theApp;