#pragma once

#include "ADOConn.h"
#include "LinkButton.h"
// CUpdatePetDlg 对话框

class CUpdatePetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdatePetDlg)

public:
	CUpdatePetDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUpdatePetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_PET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_petName;
	CString m_petPrice;
	CString m_petSpecial;
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedCancel2();
	CString m_petId;
};
