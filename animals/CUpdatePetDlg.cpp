// CUpdatePetDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CUpdatePetDlg.h"
#include "afxdialogex.h"


// CUpdatePetDlg 对话框

IMPLEMENT_DYNAMIC(CUpdatePetDlg, CDialogEx)

CUpdatePetDlg::CUpdatePetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_PET, pParent)
	, m_petName(_T(""))
	, m_petPrice(_T(""))
	, m_petSpecial(_T(""))
{

}

CUpdatePetDlg::~CUpdatePetDlg()
{
}

void CUpdatePetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PET_NAME, m_petName);
	DDX_Text(pDX, IDC_EDIT_PET_PRICE, m_petPrice);
	DDX_Text(pDX, IDC_EDIT_PET_SPECIAL, m_petSpecial);
}


BEGIN_MESSAGE_MAP(CUpdatePetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUpdatePetDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDCANCEL2, &CUpdatePetDlg::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CUpdatePetDlg 消息处理程序


void CUpdatePetDlg::OnBnClickedButtonUpdate()
{
	UpdateData();
	if (m_petName.IsEmpty()) {
		CString message = "请输入宠物名";
		AfxMessageBox(message);
		return;
	}
	if (m_petSpecial.IsEmpty()) {
		CString message = "请输入宠物种类名";
		AfxMessageBox(message);
		return;
	}
	if (m_petPrice.IsEmpty()) {
		CString message = "请输入宠物价格";
		AfxMessageBox(message);
		return;
	}
	CString sql;
	sql.Format("update pet set pet_name = '%s',pet_special='%s',pet_price='%s' where admin_id='%s' and pet_id = '%s'",
		m_petName, m_petSpecial, m_petPrice, CMyPublicData::user_id, m_petId);

	try
	{
		m_AdoConn.ExecuteSQL((_bstr_t)sql);
		m_AdoConn.ExitADOConn();
		AfxMessageBox("修改成功");
	}
	catch (...) {
		AfxMessageBox("操作失败");
		return;
	}

	CDialogEx::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}


void CUpdatePetDlg::OnBnClickedCancel2()
{
	CDialogEx::OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}
