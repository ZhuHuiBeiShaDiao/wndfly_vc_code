
// War3ToolsDlg.h : ͷ�ļ�
//

#pragma once


// CWar3ToolsDlg �Ի���
class CWar3ToolsDlg : public CDialogEx
{
// ����
public:
	CWar3ToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CWar3ToolsDlg();

// �Ի�������
	enum { IDD = IDD_WAR3TOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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


// CSetPathDlg �Ի���

class CSetPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPathDlg)

public:
	CSetPathDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetPathDlg();

// �Ի�������
	enum { IDD = IDD_SETPATH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void On32773();
};