
// War3ToolsDlg.h : 头文件
//

#pragma once


// CWar3ToolsDlg 对话框
class CWar3ToolsDlg : public CDialogEx
{
// 构造
public:
	CWar3ToolsDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CWar3ToolsDlg();

// 对话框数据
	enum { IDD = IDD_WAR3TOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};


// CSetPathDlg 对话框

class CSetPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPathDlg)

public:
	CSetPathDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPathDlg();

// 对话框数据
	enum { IDD = IDD_SETPATH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};


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
public:
	afx_msg void OnBnClickedOk();
	afx_msg void On32773();
};