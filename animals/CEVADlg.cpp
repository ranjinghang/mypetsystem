// CEVADlg.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CEVADlg.h"
#include "afxdialogex.h"


// CEVADlg 对话框

IMPLEMENT_DYNAMIC(CEVADlg, CDialogEx)

CEVADlg::CEVADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EVALUATE, pParent)
	, m_Evaluate(_T(""))
{

}

CEVADlg::~CEVADlg()
{
	
}

void CEVADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EVALUATE, m_Evaluate);
}


BEGIN_MESSAGE_MAP(CEVADlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEVADlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEVADlg 消息处理程序


void CEVADlg::OnBnClickedOk()
{
	UpdateData();
	if (m_Evaluate.IsEmpty()) {
		CString message = "评论不能为空";
		AfxMessageBox(message);
		return;
	}

	CString sql;
	sql.Format("update dogorder set evaluate = '%s' where order_no = '%s'", m_Evaluate, m_orderNo);
	m_AdoConn.ExecuteSQL((_bstr_t)sql);
	CString message("评价成功");
	m_AdoConn.ExitADOConn();
	AfxMessageBox(message);
	CDialogEx::OnOK();
}
