// tempwindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tempwindow.h"
#include "tempwindowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTempwindowDlg dialog

CTempwindowDlg::CTempwindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTempwindowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTempwindowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTempwindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTempwindowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTempwindowDlg, CDialog)
	//{{AFX_MSG_MAP(CTempwindowDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempwindowDlg message handlers

BOOL CTempwindowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//char* lpszParam;
	//int nTemp;
	//lpszParam = ::CommandLineToArgvW(GetCommandLine(),&nTemp);
	//::MessageBox(NULL,__targv[0],"����",MB_OK);
	SetWindowText(__targv[1]);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTempwindowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTempwindowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTempwindowDlg::OnNcPaint()

{
	
	static int i = 2;
	
	if(i > 0)
		
	{
		
		i --;
		
		ShowWindow(SW_HIDE);
		
	}
	
	else
		
		CDialog::OnNcPaint();
	
} 