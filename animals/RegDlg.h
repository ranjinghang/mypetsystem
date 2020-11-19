#pragma once
#include "afxwin.h"
#include "ADOConn.h"
#include "LinkButton.h"
// CRegDlg 对话框

class CRegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegDlg)

public:
	CRegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegDlg();

// 对话框数据
	enum { IDD = IDD_regis };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;


	CComboBox m_question;
	CString m_answer;
	CString m_username;
	CString m_pwd;
	CString m_pwdrepeat;
	CString m_phone;
	CString m_address;
	CString type;
	int m_radio;

	virtual BOOL OnInitDialog();
	CString m_questionselect;
	afx_msg void OnBnClickedButton1();
	UINT m_age;
	afx_msg void OnBnClickedsexmale();
	afx_msg void OnBnClickedsexfemale();
	CString m_city;
	afx_msg void OnBnClickedCancel();
	CLinkButton m_zhuce;
	CLinkButton m_chongtian;
	CLinkButton m_quxiao;
	afx_msg void OnEnChangeEdit10();
};
