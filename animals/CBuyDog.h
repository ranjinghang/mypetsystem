#pragma once
#include "ADOConn.h"
#include "afxwin.h"

// CBuyDog 对话框

class CBuyDog : public CDialogEx
{
	DECLARE_DYNAMIC(CBuyDog)

public:
	CBuyDog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBuyDog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BUY_DOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

	CString m_dog_id;
	CString m_dog_name;
	CString m_owner_id;
	CString m_user_id;
	CString m_amount;
	virtual BOOL OnInitDialog();
};
