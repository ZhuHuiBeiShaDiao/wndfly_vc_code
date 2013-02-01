
// War3ToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "War3Tools.h"
#include "War3ToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HMODULE g_hModule;

// CWar3ToolsDlg �Ի���

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


// CWar3ToolsDlg ��Ϣ�������

BOOL CWar3ToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_hModule = ::LoadLibrary(L"War3ToolsDLL.dll");
	if(g_hModule == NULL)
	{
		::MessageBox(m_hWnd,L"��̬�� War3ToolsDLL.dll ����ʧ��",L"����",MB_OK);
		CWar3ToolsDlg::OnCancel();
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWar3ToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���������������
}

void CWar3ToolsDlg::On32772()
{
	// TODO: �ڴ���������������
}

void CWar3ToolsDlg::On32773()
{
	// TODO: �ڴ���������������
	CSetPathDlg dlgSetPath;
	dlgSetPath.DoModal();
}


void CWar3ToolsDlg::On32774()
{
	// TODO: �ڴ���������������
}


void CWar3ToolsDlg::On32775()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	// TODO: �ڴ���������������
}


void CWar3ToolsDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	typedef BOOL(*pReadReg)(LPCWSTR lpRegKeyName, LPWSTR lpValue);
	LPWSTR lpValue = new WCHAR[MAX_PATH];
	LPCWSTR lpRegKeyName = L"war3path";

	pReadReg ReadReg = (pReadReg)::GetProcAddress(g_hModule,"ReadReg");
	ReadReg(lpRegKeyName,lpValue);

	if(::wcscmp(lpValue,L"") == 0)
	{
		::MessageBox(m_hWnd,L"�������б����ߣ���ѡ����ħ������Ŀ¼��",L"��ʾ",MB_OK);
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
			::MessageBox(m_hWnd,L"ħ������������",L"��ʾ",MB_OK);
		}else{
			::MessageBox(m_hWnd,L"ħ����������ʧ�ܣ�����·������",L"��ʾ",MB_OK);
		}
	}
}


void CWar3ToolsDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CWar3ToolsDlg::OnCancel();
	//return IDBUTTON4;	
}


void CWar3ToolsDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CWar3ToolsDlg::OnCancel();
	//return IDBUTTON4;	
}


void CWar3ToolsDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CWar3ToolsDlg::OnCancel();
	//return IDBUTTON4;	
}



// CSetPathDlg �Ի���

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


// CSetPathDlg ��Ϣ�������


void CSetPathDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	typedef BOOL(*pWriteReg)(LPCWSTR lpRegKeyName, LPCWSTR lpValue);
	LPWSTR lpValue = new WCHAR[MAX_PATH];
	LPCWSTR lpRegKeyName = L"war3path";

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),lpValue,MAX_PATH);

	pWriteReg WriteReg = (pWriteReg)::GetProcAddress(g_hModule,"WriteReg");
	WriteReg(lpRegKeyName,lpValue);

	::MessageBox(NULL,_T("ħ������Ŀ¼���óɹ���"),_T("��Ϣ"),MB_OK);
	CDialogEx::OnOK();
}

void CSetPathDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CSetPathDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CFileDialog dlgFile(TRUE);
	//dlgFile.DoModal();
	BROWSEINFO bi;

	TCHAR buffer[MAX_PATH];
	TCHAR szFullPath[MAX_PATH];

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.lpszTitle = _T("��ѡ��Ŀ¼");
	bi.pszDisplayName = buffer;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	bi.iImage = 0;
	bi.lParam = 0;
	bi.lpfn = NULL;

	ITEMIDLIST *pidl = ::SHBrowseForFolder(&bi);

	::SHGetPathFromIDList(pidl,szFullPath);
	
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),szFullPath);
}


// CAboutDlg �Ի���

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

// CAboutDlg ��Ϣ�������

void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
