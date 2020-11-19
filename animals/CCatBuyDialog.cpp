// CCatBuyDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CCatBuyDialog.h"
#include "afxdialogex.h"


// CCatBuyDialog 对话框

IMPLEMENT_DYNAMIC(CCatBuyDialog, CDialogEx)

CCatBuyDialog::CCatBuyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BUY_CAT, pParent)
	, m_cat_id(_T(""))
	, m_amount(_T(""))
	, m_user_id(_T(""))
{

}

CCatBuyDialog::~CCatBuyDialog()
{
}

void CCatBuyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CAT_AMOUNT, m_amount);
	DDX_Text(pDX, IDC_STATIC_CAT_ID, m_cat_id);
	DDX_Text(pDX, IDC_STATIC_USER_ID, m_user_id);
}


BEGIN_MESSAGE_MAP(CCatBuyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCatBuyDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCatBuyDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCatBuyDialog 消息处理程序


void CCatBuyDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_amount.IsEmpty()) {
		CString message = "数量不能为空";
		AfxMessageBox(message);
		return;
	}
	CTime time;
	time = CTime::GetCurrentTime();//当前系统时间
	CString nowtime = time.Format("%Y-%m-%d");

	CString sql;
	sql.Format("insert into catorder( order_name, user_id, dog_id, create_time, amount)values('%s', '%s', '%s', % d, '%s')", "购买订单", m_user_id, m_cat_id, nowtime, m_amount);
	m_AdoConn.ExecuteSQL((_bstr_t)sql);
	m_AdoConn.ExitADOConn();
	CString message("购买成功");
	AfxMessageBox(message);
	CDialogEx::OnOK();
}


void CCatBuyDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
