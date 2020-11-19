#pragma once

#include "ADOConn.h"
#include "afxwin.h"
#include "LinkButton.h"
// CFindpwdDlg �Ի���

class CFindpwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindpwdDlg)

public:
	CFindpwdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindpwdDlg();

// �Ի�������
	enum { IDD = IDD_FINDPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

	//CString m_staticusername;
	//CString m_staticquestion;
	//CString m_staticpwd;
	CString Name;
	CString m_answer;
	afx_msg void OnBnClickedOk();
	CStatic m_staticusername;
	CStatic m_staticquestion;
	CStatic m_staticpwd;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	CLinkButton m_tijiao;
	CLinkButton m_fanhui;
};
