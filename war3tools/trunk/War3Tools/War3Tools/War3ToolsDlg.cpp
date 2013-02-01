
// War3ToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "War3Tools.h"
#include "War3ToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HMODULE g_hModule;

// CWar3ToolsDlg 对话框

CWar3ToolsDlg::CWar3ToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWar3ToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWar3ToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWar3ToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CWar3ToolsDlg::On32771)
	ON_COMMAND(ID_32772, &CWar3ToolsDlg::On32772)
	ON_COMMAND(ID_32773, &CWar3ToolsDlg::On32773)
	ON_COMMAND(ID_32774, &CWar3ToolsDlg::On32774)
	ON_COMMAND(ID_32775, &CWar3ToolsDlg::On32775)
	ON_BN_CLICKED(IDC_BUTTON1, &CWar3ToolsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWar3ToolsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWar3ToolsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CWar3ToolsDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CWar3ToolsDlg 消息处理程序

BOOL CWar3ToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_hModule = ::LoadLibrary(L"War3ToolsDLL.dll");
	if(g_hModule == NULL)
	{
		::MessageBox(m_hWnd,L"动态库 War3ToolsDLL.dll 加载失败",L"错误",MB_OK);
		CWar3ToolsDlg::OnCancel();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWar3ToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWar3ToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWar3ToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CWar3ToolsDlg::~CWar3ToolsDlg()
{
	::FreeLibrary(g_hModule);
}

void CWar3ToolsDlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
}

void CWar3ToolsDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
}

void CWar3ToolsDlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	CSetPathDlg dlgSetPath;
	dlgSetPath.DoModal();
}


void CWar3ToolsDlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
}


void CWar3ToolsDlg::On32775()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	// TODO: 在此添加命令处理程序代码
}


void CWar3ToolsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	typedef BOOL(*pReadReg)(LPCWSTR lpRegKeyName, LPWSTR lpValue);
	LPWSTR lpValue = new WCHAR[MAX_PATH];
	LPCWSTR lpRegKeyName = L"war3path";

	pReadReg ReadReg = (pReadReg)::GetProcAddress(g_hModule,"ReadReg");
	ReadReg(lpRegKeyName,lpValue);

	if(::wcscmp(lpValue,L"") == 0)
	{
		::MessageBox(m_hWnd,L"初次运行本工具，请选设置魔兽争霸目录！",L"提示",MB_OK);
		CSetPathDlg dlgSetPath;
		dlgSetPath.DoModal();
	}else{
		LPCWSTR lpWar3 = L"\\war3.exe";
		::wcscat_s(lpValue,::wcslen(lpWar3) * 2,lpWar3);

		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;

		LONG lRet = ::CreateProcess(NULL, lpValue, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
		if(lRet)
		{
			::CloseHandle (pi.hThread);
			::CloseHandle (pi.hProcess);
			::MessageBox(m_hWnd,L"魔兽争霸已启动",L"提示",MB_OK);
		}else{
			::MessageBox(m_hWnd,L"魔兽争霸启动失败，请检查路径设置",L"提示",MB_OK);
		}
	}
}


void CWar3ToolsDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//CWar3ToolsDlg::OnCancel();
	//return IDBUTTON4;	
}


void CWar3ToolsDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//CWar3ToolsDlg::OnCancel();
	//return IDBUTTON4;	
}


void CWar3ToolsDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//CWar3ToolsDlg::OnCancel();
	//return IDBUTTON4;	
}



// CSetPathDlg 对话框

IMPLEMENT_DYNAMIC(CSetPathDlg, CDialogEx)

CSetPathDlg::CSetPathDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetPathDlg::IDD, pParent)
{
	typedef BOOL(*pReadReg)(LPCWSTR lpRegKeyName, LPWSTR lpValue);
	LPWSTR lpValue = new WCHAR[MAX_PATH];
	LPCWSTR lpRegKeyName = L"war3path";

	pReadReg ReadReg = (pReadReg)::GetProcAddress(g_hModule,"ReadReg");
	ReadReg(lpRegKeyName,lpValue);

	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),lpValue);
}

CSetPathDlg::~CSetPathDlg()
{
}

void CSetPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPathDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CSetPathDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetPathDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CSetPathDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPathDlg 消息处理程序


void CSetPathDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	typedef BOOL(*pWriteReg)(LPCWSTR lpRegKeyName, LPCWSTR lpValue);
	LPWSTR lpValue = new WCHAR[MAX_PATH];
	LPCWSTR lpRegKeyName = L"war3path";

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),lpValue,MAX_PATH);

	pWriteReg WriteReg = (pWriteReg)::GetProcAddress(g_hModule,"WriteReg");
	WriteReg(lpRegKeyName,lpValue);

	::MessageBox(NULL,_T("魔兽争霸目录设置成功！"),_T("信息"),MB_OK);
	CDialogEx::OnOK();
}

void CSetPathDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CSetPathDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlgFile(TRUE);
	//dlgFile.DoModal();
	BROWSEINFO bi;

	TCHAR buffer[MAX_PATH];
	TCHAR szFullPath[MAX_PATH];

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.lpszTitle = _T("请选择目录");
	bi.pszDisplayName = buffer;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	bi.iImage = 0;
	bi.lParam = 0;
	bi.lpfn = NULL;

	ITEMIDLIST *pidl = ::SHBrowseForFolder(&bi);

	::SHGetPathFromIDList(pidl,szFullPath);
	
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),szFullPath);
}


// CAboutDlg 对话框

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAboutDlg 消息处理程序

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
