
// CmagicPDFDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CmagicPDF.h"
#include "CmagicPDFDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct PDF_PARAM
{
	INT nWidth;
	INT nHeight;
	INT nX;
	INT nY;
	INT nCellX;
	INT nCellY;
	BOOL bDocModel;
	FLOAT fScale;
}PDF_PARAM_LIST;

INT GetFileLine(LPCTSTR lpFileName);
BOOL ReadCSVFile(LPCTSTR lpFileName, LPTSTR* lplpFilelist);
BOOL SelectDir(HWND hwnd, LPTSTR lpszDir);
BOOL GetDir(LPTSTR lpDecPath, LPCTSTR lpSrcPath1, LPCTSTR lpSrcPath2);
BOOL CheckDir(LPTSTR lpszPath);
BOOL CreatePDF(LPCTSTR lpszInPath, LPCTSTR lpszOutPath, PDF_PARAM_LIST* lpppl, LPTSTR* lplpImageFileList, DWORD dwListCount);


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCmagicPDFDlg 对话框




CCmagicPDFDlg::CCmagicPDFDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCmagicPDFDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CCmagicPDFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCmagicPDFDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCmagicPDFDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCmagicPDFDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CCmagicPDFDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCmagicPDFDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCmagicPDFDlg 消息处理程序

BOOL CCmagicPDFDlg::OnInitDialog()
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

	//::SetRadio(::GetDlgItem(m_hWnd, IDC_RADIO1)
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//单选选中
	((CDialog *)GetDlgItem(IDC_EDIT3))->SetWindowText(_T("2500"));
	((CDialog *)GetDlgItem(IDC_EDIT4))->SetWindowText(_T("2500"));
	((CDialog *)GetDlgItem(IDC_EDIT5))->SetWindowText(_T("240"));
	((CDialog *)GetDlgItem(IDC_EDIT6))->SetWindowText(_T("240"));
	((CDialog *)GetDlgItem(IDC_EDIT7))->SetWindowText(_T("10"));
	((CDialog *)GetDlgItem(IDC_EDIT8))->SetWindowText(_T("10"));
	((CDialog *)GetDlgItem(IDC_EDIT9))->SetWindowText(_T("100"));
	//GetDlgItem(IDC_EDIT1)->

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCmagicPDFDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCmagicPDFDlg::OnPaint()
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
HCURSOR CCmagicPDFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCmagicPDFDlg::OnBnClickedButton1()
{
	TCHAR szFullPath[MAX_PATH] = {};
	TCHAR szFullPath1[MAX_PATH] = {};
	LPCTSTR lpPdfDir = _T("PDF");
	BOOL bRet;

	bRet = SelectDir(m_hWnd, szFullPath);

	if(bRet)
	{
		if(::_tcscmp(szFullPath,_T("")) != 0)
		{
			::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),szFullPath);

			::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT2),szFullPath1,MAX_PATH);

			if(::_tcscmp(szFullPath1,_T("")) == 0)
			{
				bRet = GetDir(szFullPath1, szFullPath, lpPdfDir);

				if(bRet)
				{
					::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT2),szFullPath1);
				}
				

			}
		}
	}

	
}


void CCmagicPDFDlg::OnBnClickedButton2()
{
	TCHAR szFullPath[MAX_PATH] = {};
	BOOL bRet;

	bRet = SelectDir(m_hWnd, szFullPath);

	if(bRet)
	{
		if(::_tcscmp(szFullPath,_T("")) != 0){
			::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT2),szFullPath);
		}
	}
}


void CCmagicPDFDlg::OnBnClickedOk()
{
	INT nCount;
	BOOL bRet,bRet1,bRet2;
	LPTSTR* lplpFileList;
	TCHAR szdir[MAX_PATH] = {};
	TCHAR szFullPath[MAX_PATH] = {};
	TCHAR szFullPath1[MAX_PATH] = {};

	PDF_PARAM_LIST ppl;
	TCHAR szTemp[10] = {};
	BOOL bCheck;

	// 获取参数的设置
	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT3),szTemp,10);
	ppl.nWidth = ::StrToInt(szTemp);

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT4),szTemp,10);
	ppl.nHeight = ::StrToInt(szTemp);

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT5),szTemp,10);
	ppl.nX = ::StrToInt(szTemp);

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT6),szTemp,10);
	ppl.nY = ::StrToInt(szTemp);

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT7),szTemp,10);
	ppl.nCellX = ::StrToInt(szTemp);

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT8),szTemp,10);
	ppl.nCellY = ::StrToInt(szTemp);

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT9),szTemp,10);
	ppl.fScale= (FLOAT)::StrToInt(szTemp) / 100;

	bCheck = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	if(bCheck)
	{
		ppl.bDocModel = TRUE;
	}else{
		ppl.bDocModel = FALSE;
	}

	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),szFullPath,MAX_PATH);
	::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT2),szFullPath1,MAX_PATH);

	//~

	if(::_tcscmp(szFullPath,_T("")) != 0)
	{
		bRet = GetDir(szdir, szFullPath, _T("index.csv"));
		bRet1 = CheckDir(szFullPath1);

		if(bRet && bRet1)
		{
			nCount = GetFileLine(szdir);
			lplpFileList = new TCHAR* [nCount];

			bRet2 = ReadCSVFile(szdir,lplpFileList);

			if(bRet2)
			{
				/*for(int i = 0; i < nCount; i++)
				{
					::MessageBox(NULL, lplpFileList[i], _T("文件内容"), MB_OK);
				}*/
				CreatePDF(szFullPath, szFullPath1, &ppl, lplpFileList, nCount);
			}

			for(int i = 0; i < nCount; i++)
			{
				delete [] lplpFileList[i];
			}
			delete [] lplpFileList;

			::MessageBox(NULL, _T("生成PDF文件已完成"), _T("消息"), MB_ICONINFORMATION);
		}
		//nRet = ReadCSV(szFullPath,szFullPath1,_T("index.csv"),lplp);
	}else{
		::MessageBox(NULL, _T("请选择彩码目录"), _T("提示"), MB_ICONINFORMATION);
	}

	//CDialogEx::OnOK();
}

void CCmagicPDFDlg::OnBnClickedCancel()
{
	//create_pdf();
	// TODO: 在此添加控件通知处理程序代码
	
	//INT nRet;
	//BOOL bRet;

	//bRet = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	//CheckRadioButton(IDC_RADIO1,IDC_RADIO2,nRet);
	CDialogEx::OnCancel();

}

/*
BOOL ByteToUnicode(LPVOID lpBuffer, LPTSTR lpszUnicode)
{
	BOOL bRet;
	DWORD dwFileCb;
	DWORD dwFileSize;
	DWORD dwStringSize;
	LPVOID lpBuffer;
	LPTSTR lpszText;
	LPTSTR lpszTextTemp;
	HANDLE hFile;

	dwStringSize = MultiByteToWideChar (CP_MACCP, 0, (LPCSTR)lpBuffer, -1, NULL, 0);
	lpszText = new TCHAR[dwStringSize];

	MultiByteToWideChar (CP_MACCP, 0, (LPCSTR)lpBuffer, -1, lpszText, dwStringSize);
};
*/

BOOL CheckDir(LPTSTR lpszPath)
{
	SECURITY_ATTRIBUTES sa;
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	BOOL bRet;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = FALSE;
 
	hFind = FindFirstFile(lpszPath, &wfd);  
	if(hFind == INVALID_HANDLE_VALUE)
	{  
		 bRet = CreateDirectory(lpszPath,&sa);
		 if(!bRet)
		 {
			 return FALSE;
		 }
	}  

	FindClose(hFind);

	return TRUE;
}

BOOL SelectDir(HWND hwnd, LPTSTR lpszDir)
{
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	TCHAR buffer[MAX_PATH] = {};

	bi.hwndOwner = hwnd;
	bi.pidlRoot = NULL;
	bi.lpszTitle = _T("请选择目录");
	bi.pszDisplayName = buffer;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	bi.iImage = 0;
	bi.lParam = 0;
	bi.lpfn = NULL;

	try
	{
		pidl = ::SHBrowseForFolder(&bi);

		::SHGetPathFromIDList(pidl,lpszDir);

		return TRUE;
	}
	catch (CFileException* e)
	{
		return FALSE;
	}

}

BOOL GetDir(LPTSTR lpszDecPath, LPCTSTR lpszSrcPath1, LPCTSTR lpszSrcPath2)
{
	LPTSTR lpszSyb = _T("\\");
	INT nLenPath1 = ::_tcslen(lpszSrcPath1);
	INT nLenPath2 = ::_tcslen(lpszSrcPath2);

	try
	{
		::_tcscpy(lpszDecPath, lpszSrcPath1);
		if(lpszSrcPath1[nLenPath1 - 1] != '\\')
		{
			::_tcscat(lpszDecPath, lpszSyb);
		}
		::_tcscat(lpszDecPath, lpszSrcPath2);

		return TRUE;
	}
	catch (CMemoryException* e)
	{
		return FALSE;
	}
}

INT GetFileLine(LPCTSTR lpFileName)
{
	BOOL bRet;
	DWORD dwFileCb;
	DWORD dwFileSize;
	//DWORD dwStringSize;
	LPBYTE lpBuffer;
	LPTSTR lpszText;
	LPTSTR lpszTextTok;
	HANDLE hFile;

	INT nCount = 0;

	hFile = ::CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{

		dwFileSize = ::GetFileSize(hFile,NULL);

		if(dwFileSize == 0)
		{
			::CloseHandle(hFile);
			return nCount;
		}

		//BYTE Buffer[65535] = {};
		lpBuffer = new BYTE[dwFileSize + 1];
		//::memset(Buffer,65,10);

		bRet = ::ReadFile(hFile,lpBuffer,dwFileSize,&dwFileCb,NULL);
		lpBuffer[dwFileSize] = 0;
		//::MessageBoxA(NULL,(char *)lpBuffer,"消息",MB_OK);
		
		if(bRet)
		{
			// 将字节串转化成Unicode字符串
			//dwStringSize = MultiByteToWideChar (CP_ACP, 0, (LPCSTR)lpBuffer, -1, NULL, 0);
			lpszText = new TCHAR[dwFileSize + 1];

			MultiByteToWideChar (CP_ACP, 0, (LPCSTR)lpBuffer, -1, lpszText, dwFileSize);
			// ~
			lpszText[dwFileSize] = 0;
			//lpszTextTemp = new TCHAR[dwStringSize];

			lpszTextTok = ::_tcstok(lpszText,_T("\n"));
			while(lpszTextTok != NULL)
			{
				//if(::_tcscmp(lpszTextTok,_T("")) != 0){
				//nCount++;
				//}
				for(int i = 0; i < ::_tcslen(lpszTextTok); i++)
				{
					if(lpszTextTok[i] != _T(' '))
					{
 						nCount++;
						break;
					}
				}
				lpszTextTok = ::_tcstok(NULL,_T("\n"));
			}
		}
	}

	::CloseHandle(hFile);
	delete []lpszText;
	delete []lpBuffer;

	return nCount;

}

BOOL ReadCSVFile(LPCTSTR lpFileName, LPTSTR* lplpFileList)
{
	BOOL bRet;
	DWORD dwFileCb;
	DWORD dwFileSize;
	LPBYTE lpBuffer;
	LPTSTR lpszText;
	LPTSTR lpszTextTok;
	HANDLE hFile;
	INT nCount = 0;
	//TCHAR szdir[MAX_PATH] = {};

	//::StrNCatW(szdir, lpSrcPath, wcslen(lpSrcPath) + 1);
	//::StrNCatW(szdir, lptstr, wcslen(lptstr) + 1);
	//::StrNCatW(szdir, lpFileNameCSV, wcslen(lpFileNameCSV) + 1);

	hFile = ::CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		
		dwFileSize = ::GetFileSize(hFile,NULL);

		if(dwFileSize == 0)
		{
			::CloseHandle(hFile);
			return FALSE;
		}

		lpBuffer = new BYTE[dwFileSize + 1];

		bRet = ::ReadFile(hFile,lpBuffer,dwFileSize,&dwFileCb,NULL);
		lpBuffer[dwFileSize] = 0;

		if(bRet)
		{
			// 将字节串转化成Unicode字符串
			lpszText = new TCHAR[dwFileSize + 1];

			MultiByteToWideChar (CP_ACP, 0, (LPCSTR)lpBuffer, -1, lpszText, dwFileSize);
			// ~
			lpszText[dwFileSize] = 0;


			lpszTextTok = ::_tcstok(lpszText,_T("\n"));

			while(lpszTextTok != NULL)
			{
				for(int i = 0; i < ::_tcslen(lpszTextTok); i++)
				{
					if(lpszTextTok[i] != _T(' '))
					{
						try
						{
							lplpFileList[nCount] = new TCHAR[::_tcslen(lpszTextTok) + 1];
							//lplpFilelist[nCount][::_tcslen(lpszTextTok)] = '\0';
							::_tcscpy(lplpFileList[nCount], lpszTextTok);
							nCount++;
							break;
						}
						catch (CException* e)
						{
							return FALSE;
						}
					}
				}

				lpszTextTok = ::_tcstok(NULL,_T("\n"));
			}

			//delete [] lplpFilelist[1];

			for(int i = 0; i < nCount; i++)
			{
				lpszTextTok = ::_tcstok(lplpFileList[i],_T(","));
				int j = 0;

				while(lpszTextTok != NULL)
				{
					if(j == 6)
					{
						//delete [] lplpFilelist[i];
						//lplpFilelist[i] = new TCHAR[::_tcslen(lpszTextTok) + 1];
						::_tcscpy(lplpFileList[i], lpszTextTok);
						break;
					}

					lpszTextTok = ::_tcstok(NULL,_T(","));
					j++;
				}
			}
		}

		::CloseHandle(hFile);

		delete [] lpBuffer;
		delete [] lpszText;

		return TRUE;
	}else{
		::CloseHandle(hFile);
		return FALSE;
	}
}

BOOL CreatePDF(LPCTSTR lpszInPath, LPCTSTR lpszOutPath, PDF_PARAM_LIST* lpppl, LPTSTR* lplpImageFileList, DWORD dwListCount)
{
	INT nPage,nPageSum,nCountX,nCountY,nSpaceX,nSpaceY,nCurrentNum,nImage;
	DWORD dwLen;
	BOOL bRet;
	LPTSTR lpszFileName = _T("Cmagic.pdf");
	LPTSTR lpszTextTok1 = _T("Cmagic");
	LPTSTR lpszTextTok2 = _T(".pdf");
	LPSTR lpszTempText;
	LPSTR lpszTempText1;
	TCHAR szTempPath[MAX_PATH] = {};
	TCHAR szTempPath1[MAX_PATH] = {};
	TCHAR szTempStr[10] = {};
	TCHAR szTempFileName[MAX_PATH] = {};

	nCountX = (INT)((lpppl->nWidth + lpppl->nCellX) / (lpppl->nX * lpppl->fScale + lpppl->nCellX));
	nCountY = (INT)((lpppl->nHeight + lpppl->nCellY) / (lpppl->nY * lpppl->fScale + lpppl->nCellY));
	nSpaceX = (INT)((lpppl->nWidth - nCountX * lpppl->nX * lpppl->fScale - (nCountX - 1) * lpppl->nCellX) / 2);
	nSpaceY = (INT)((lpppl->nHeight - nCountY * lpppl->nY * lpppl->fScale - (nCountY - 1) * lpppl->nCellY) / 2); 

	nPageSum = nCountX * nCountY;
	nPage = (INT)(dwListCount / nPageSum);

	if(lpppl->bDocModel)
	{
		PDF *pdf = PDF_new();

		if(pdf)
		{
			bRet = GetDir(szTempPath,lpszOutPath,lpszFileName);
			if(!bRet)
			{
				PDF_close(pdf);
				return FALSE;
			}

			dwLen = WideCharToMultiByte(CP_OEMCP,NULL,szTempPath,-1,NULL,0,NULL,FALSE);
			lpszTempText = new CHAR[dwLen];

			WideCharToMultiByte (CP_OEMCP,NULL,szTempPath,-1,lpszTempText,dwLen,NULL,FALSE);

			try
			{
				PDF_open_file(pdf,lpszTempText);

				for(int i = 0; i <= nPage; i++)
				{
					PDF_begin_page(pdf, lpppl->nWidth, lpppl->nHeight);

					for(int j = 0; j < nCountY; j++)
					{
						for(int k = 0; k < nCountX; k++)
						{
							nCurrentNum = i * nPageSum + j * nCountX + k;
							if(nCurrentNum < dwListCount)
							{
								bRet = GetDir(szTempPath1,lpszInPath,lplpImageFileList[nCurrentNum]);
								if(!bRet)
								{
									PDF_close(pdf);
									delete [] lpszTempText;
									return FALSE;
								}

								dwLen = WideCharToMultiByte(CP_OEMCP,NULL,szTempPath1,-1,NULL,0,NULL,FALSE);
								lpszTempText1 = new CHAR[dwLen];

								WideCharToMultiByte (CP_OEMCP,NULL,szTempPath1,-1,lpszTempText1,dwLen,NULL,FALSE);

								nImage = PDF_open_image_file(pdf, "jpeg", lpszTempText1, "", 0);

								PDF_place_image(pdf, nImage, (lpppl->nX * lpppl->fScale + lpppl->nCellX) * k + nSpaceX, lpppl->nHeight - (lpppl->nY * lpppl->fScale + lpppl->nCellY) * (j + 1) - nSpaceY, lpppl->fScale); 
								PDF_close_image(pdf, nImage);

								delete [] lpszTempText1;
							}
						}
					}

					PDF_end_page(pdf);
				}

				PDF_close(pdf);
				delete [] lpszTempText;
			}
			catch (CException* e)
			{
				::MessageBox(NULL, _T("PDF文件已打开或目录为只读"), _T("提示"), MB_ICONINFORMATION);
			}

			return TRUE;
		}else{
			PDF_close(pdf);
			return FALSE;
		}
	}else{

		//lpszTextTok1 = ::_tcstok(lpszFileName,_T("."));
		//lpszTextTok2 = ::_tcstok(NULL,_T("."));

		PDF *pdf = PDF_new();

		if(pdf)
		{
			for(int i = 0; i <= nPage; i++)
			{				
				::_stprintf(szTempStr, _T("%03d"), i);
				::_tcscpy(szTempFileName, lpszTextTok1);
				::_tcscat(szTempFileName, szTempStr);
				::_tcscat(szTempFileName, lpszTextTok2);

				bRet = GetDir(szTempPath,lpszOutPath,szTempFileName);
				if(!bRet)
				{
					PDF_close(pdf);
					return FALSE;
				}

				dwLen = WideCharToMultiByte(CP_OEMCP,NULL,szTempPath,-1,NULL,0,NULL,FALSE);
				lpszTempText = new CHAR[dwLen];

				WideCharToMultiByte (CP_OEMCP,NULL,szTempPath,-1,lpszTempText,dwLen,NULL,FALSE);

				try
				{
					PDF_open_file(pdf,lpszTempText);
					PDF_begin_page(pdf, lpppl->nWidth, lpppl->nHeight);

					for(int j = 0; j < nCountY; j++)
					{
						for(int k = 0; k < nCountX; k++)
						{
							nCurrentNum = i * nPageSum + j * nCountX + k;
							if(nCurrentNum < dwListCount)
							{
								bRet = GetDir(szTempPath1,lpszInPath,lplpImageFileList[nCurrentNum]);
								if(!bRet)
								{
									PDF_close(pdf);
									delete [] lpszTempText;
									return FALSE;
								}

								dwLen = WideCharToMultiByte(CP_OEMCP,NULL,szTempPath1,-1,NULL,0,NULL,FALSE);
								lpszTempText1 = new CHAR[dwLen];

								WideCharToMultiByte (CP_OEMCP,NULL,szTempPath1,-1,lpszTempText1,dwLen,NULL,FALSE);

								nImage = PDF_open_image_file(pdf, "jpeg", lpszTempText1, "", 0);

								PDF_place_image(pdf, nImage, (lpppl->nX * lpppl->fScale + lpppl->nCellX) * k + nSpaceX, lpppl->nHeight - (lpppl->nY * lpppl->fScale + lpppl->nCellY) * (j + 1) - nSpaceY, lpppl->fScale); 
								PDF_close_image(pdf, nImage);

								delete [] lpszTempText1;
							}
						}
					}

					PDF_end_page(pdf);
					PDF_close(pdf);

					delete [] lpszTempText;

				}
				catch (CException* e)
				{
					::MessageBox(NULL, _T("PDF文件已打开或目录为只读"), _T("提示"), MB_ICONINFORMATION);
				}
			}

			return TRUE;
		}else{
			PDF_close(pdf);
			return FALSE;
		}
	}

	//::GetWindowText(::GetDlgItem(m_hwnd,IDC_EDIT3),sz,5);

	/*PDF *pdf = PDF_new();
	if ( pdf ){
		PDF_open_file(pdf,"1.pdf");
		for ( int i = 0; i < 3; ++i ){
			int nImage = PDF_open_image_file(pdf,"jpeg","F:\\Project\\VC++\\CmagicPDF\\CmagicPDF\\pdflib\\a0000b00004770\\00cca8148fc3cefbd66037586548f63c.jpeg","",0);
			//int nImage = PDF_open_image_file(pdf,"jpeg","F:\\1.jpg","",0);
			PDF_begin_page(pdf,3600,1680);
			PDF_place_image(pdf, nImage, 0, 1440, 1); 
			PDF_close_image(pdf, nImage);

			int nImage1 = PDF_open_image_file(pdf,"jpeg","F:\\Project\\VC++\\CmagicPDF\\CmagicPDF\\pdflib\\a0000b00004770\\00d38a997fde8ed5b821eed557db0c14.jpeg","",0);
			PDF_place_image(pdf, nImage1, 250, 1440, 1); 
			PDF_close_image(pdf, nImage1);
			PDF_end_page(pdf);
		}

		PDF_close(pdf);
	}*/
}

