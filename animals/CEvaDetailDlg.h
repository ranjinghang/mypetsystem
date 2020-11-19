#pragma once

#include "ADOConn.h"
// CEvaDetailDlg 对话框

class CEvaDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEvaDetailDlg)

public:
	CEvaDetailDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEvaDetailDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EVA_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
	CString m_orderNo;
	CEdit m_EditEva;
	CEdit m_EditOrderNo;
};
