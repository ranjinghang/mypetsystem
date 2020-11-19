// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "RegDlg.h"
#include "FindpwdDlg.h"
#include "CAdminFunctionDlg.h"
#include "CUserFunctionDlg.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_strusername(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strusername);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDOK, m_queding);
	DDX_Control(pDX, IDCANCEL, m_quxiao);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CString str;
	if (m_strusername.IsEmpty())
	{
		CString str("用户名不能为空");
		MessageBox(str);
		return;
	}
	if (m_pwd.IsEmpty())
	{
		CString str("密码不能为空");
		MessageBox(str);
		return;
	}

	CString sql("select*from login where user_id='");
	CString sql2("' and pw='");
	CString sql3("' and type='admin'");
	CString sql4("' and type='user'");
	sql.Append(m_strusername);
	sql.Append(sql2);
	sql.Append(m_pwd);
	if (((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->GetCheck()) {
		sql.Append(sql3);
	}
	else {
		sql.Append(sql4);
	}

	try
	{
		m_AdoConn.OnInitADOConn();
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		if (m_pRs->adoEOF)
		{
			CString sql3("select*from login where user_id='");
			sql3.Append(m_strusername);
			sql3.AppendChar('\'');
			m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql3);
			if (!m_pRs->adoEOF)
			{
				CString type = m_pRs->GetCollect("type");
				if (((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->GetCheck()) {
					if (type.CompareNoCase("admin")) {
						CString errorMessage("用户类型错误");
						AfxMessageBox(errorMessage);
						return;
					}
				}
				else {
					if (type.CompareNoCase("user")) {
						CString errorMessage("用户类型错误");
						AfxMessageBox(errorMessage);
						return;
					}
				}
				if (m_pwd != (char*)(_bstr_t)m_pRs->GetCollect("pw"))
				{
					CString str("密码错误,是否找回密码?");
					CString str2("提示");
					if (MessageBox(str,str2 , MB_YESNO) == IDYES)
					{
						CFindpwdDlg dlg;
						dlg.Name = m_strusername;
						CDialog::OnCancel();
						dlg.DoModal();

					}
				}
			}
			else
			{
				CString str("用户名不存在，是否注册？");
				CString str2("提示");
				if (MessageBox(str, str2, MB_YESNO) == IDYES)
				{
					
					CRegDlg dlg;
					dlg.m_username = m_strusername;
					CDialog::OnCancel();
					dlg.DoModal();
					CLoginDlg dd;
					dd.DoModal();

				}
				else
					CDialog::OnCancel();
			}
		}
		else
		{
			//登录成功则打开主界面
			//CMainDlg dlg;
			//dlg.DoModal();
			CMyPublicData::user_id = m_strusername;
			if (((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->GetCheck()) {
				CAdminFunctionDlg cAdminFunctionDlg;
				cAdminFunctionDlg.DoModal();
			}
			else {
				CUserFunctionDlg cUserDlg;
				cUserDlg.DoModal();
			}
			//islogin = 1;

		}
		m_AdoConn.ExitADOConn();
	}
	catch (...)
	{
		CString errorMessage("操作失败");
		AfxMessageBox(errorMessage);
		return;
	}
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton*)GetDlgItem(IDC_RADIO_ADMIN))->SetCheck(TRUE); //选上
	((CButton*)GetDlgItem(IDC_RADIO_USER))->SetCheck(FALSE);//不选上
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
