#pragma once


// CUploadPetDlg 对话框
#include "afxwin.h"
#include "ADOConn.h"
#include "LinkButton.h"


class CUploadPetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUploadPetDlg)


public:
	CUploadPetDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUploadPetDlg();
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
	CString m_petName;
	CString m_petSpecial;
	CString m_petPrice;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPLAOD_PET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
