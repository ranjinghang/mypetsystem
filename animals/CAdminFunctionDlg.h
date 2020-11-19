#pragma once

#include "ADOConn.h"
#include "CListCtrlCl.h"
// CAdminFunctionDlg 对话框

class CAdminFunctionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminFunctionDlg)

public:
	CAdminFunctionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdminFunctionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_FUNCTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUpload();
	virtual BOOL OnInitDialog();
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
	afx_msg void OnBnClickedButtonPlease();
	CListCtrlCl m_CListCtrlCl;
	afx_msg void OnBnClickedButtonFind();
};
