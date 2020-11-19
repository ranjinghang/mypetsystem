// CUploadPetDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CUploadPetDlg.h"
#include "afxdialogex.h"


// CUploadPetDlg 对话框

IMPLEMENT_DYNAMIC(CUploadPetDlg, CDialogEx)

CUploadPetDlg::CUploadPetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPLAOD_PET, pParent)
	, m_petName(_T(""))
	, m_petSpecial(_T(""))
	, m_petPrice(_T(""))
{

}

CUploadPetDlg::~CUploadPetDlg()
{
}

void CUploadPetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PET_NAME, m_petName);
	DDX_Text(pDX, IDC_EDIT_PET_SPECIAL, m_petSpecial);
	DDX_Text(pDX, IDC_EDIT_PET_PRICE, m_petPrice);
}


BEGIN_MESSAGE_MAP(CUploadPetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUploadPetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUploadPetDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUploadPetDlg 消息处理程序


void CUploadPetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	sql.Format("insert into pet(pet_name,pet_special,pet_price,admin_id) values('%s','%s','%s','%s')",
		m_petName, m_petSpecial, m_petPrice, CMyPublicData::user_id);

	try
	{
		m_AdoConn.ExecuteSQL((_bstr_t)sql);
		m_AdoConn.ExitADOConn();
		AfxMessageBox("上传成功");
	}
	catch (...) {
		AfxMessageBox("操作失败");
		return;
	}
	
	CDialogEx::OnOK();
}


void CUploadPetDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
