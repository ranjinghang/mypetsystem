#pragma once

#include "ADOConn.h"
// CEVADlg 对话框

class CEVADlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEVADlg)

public:
	CEVADlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEVADlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EVALUATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Evaluate;
	afx_msg void OnBnClickedOk();
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
	CString m_orderNo;
};
