#pragma once

#include "ADOConn.h"
#include "CListCtrlCl.h"
// CUserFunctionDlg 对话框

class CUserFunctionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserFunctionDlg)

public:
	CUserFunctionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserFunctionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER_FUNCTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrlCl m_CListCtrlCl;
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
	afx_msg void OnBnClickedButtonPetList();
	afx_msg void OnBnClickedButtonOrder();
	BOOLEAN m_flag;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonJiyang();
};
