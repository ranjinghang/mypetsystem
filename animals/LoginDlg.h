#pragma once
#include "ADOConn.h"
#include "afxwin.h"
#include "LinkButton.h"
// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_login };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

	CString m_strusername;
	CString m_pwd;
	afx_msg void OnBnClickedCancel();
	CLinkButton m_queding;
	CLinkButton m_quxiao;
	virtual BOOL OnInitDialog();
};
