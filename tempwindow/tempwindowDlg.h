// tempwindowDlg.h : header file
//

#if !defined(AFX_TEMPWINDOWDLG_H__5A4CD969_6340_45C2_9F0A_BA6DE8378298__INCLUDED_)
#define AFX_TEMPWINDOWDLG_H__5A4CD969_6340_45C2_9F0A_BA6DE8378298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTempwindowDlg dialog

class CTempwindowDlg : public CDialog
{
// Construction
public:
	CTempwindowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTempwindowDlg)
	enum { IDD = IDD_TEMPWINDOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempwindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTempwindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPWINDOWDLG_H__5A4CD969_6340_45C2_9F0A_BA6DE8378298__INCLUDED_)
