
// War3Tools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWar3ToolsApp:
// �йش����ʵ�֣������ War3Tools.cpp
//

class CWar3ToolsApp : public CWinApp
{
public:
	CWar3ToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWar3ToolsApp theApp;