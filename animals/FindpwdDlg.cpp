// FindpwdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "FindpwdDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// CFindpwdDlg 对话框

IMPLEMENT_DYNAMIC(CFindpwdDlg, CDialogEx)

CFindpwdDlg::CFindpwdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindpwdDlg::IDD, pParent)
	, m_answer(_T(""))
{

}

CFindpwdDlg::~CFindpwdDlg()
{
}

void CFindpwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_answer);
	DDX_Control(pDX, IDC_STATIC1, m_staticusername);
	DDX_Control(pDX, IDC_STATIC2, m_staticquestion);
	DDX_Control(pDX, IDC_STATIC3, m_staticpwd);
	DDX_Control(pDX, IDOK, m_tijiao);
	DDX_Control(pDX, IDCANCEL, m_fanhui);
}


BEGIN_MESSAGE_MAP(CFindpwdDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFindpwdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFindpwdDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFindpwdDlg 消息处理程序


void CFindpwdDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	CString name, question;
	m_staticusername.GetWindowText(name);
	CString sql("select * from login where user_id ='");
	sql.Append(name);
	CString sql2("' and answer='");
	sql.Append(sql2);
	sql.Append(m_answer);
	sql.AppendChar('\'');
	try
	{
		m_AdoConn.OnInitADOConn();
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		if (!m_pRs->adoEOF)
		{
			CString str((char*)(_bstr_t)m_pRs->GetCollect("pw"));
			CString str2("回答正确，您的密码是");
			m_staticpwd.SetWindowText(str2 + str);
		}
		else
		{
			CString errorMessage("回答错误");
			m_staticpwd.SetWindowText(errorMessage);
		}
	}
	catch (...)
	{
		CString errorMessage("操作失败");
		AfxMessageBox(errorMessage);
		return;
	}
	m_AdoConn.ExitADOConn();
}


BOOL CFindpwdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_staticusername.SetWindowText(Name);
	CString sql("select * from login where user_id='");
	sql.Append(Name);
	sql.AppendChar('\'');
	try
	{
		m_AdoConn.OnInitADOConn();
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		CString question((char*)(_bstr_t)m_pRs->GetCollect("question"));
		m_staticquestion.SetWindowText(question);
		m_AdoConn.ExitADOConn();
	}
	catch (...)
	{
		CString errorMessage("操作失败");
		AfxMessageBox(errorMessage);
		return false;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CFindpwdDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CLoginDlg dlg;
	CDialog::OnCancel();
	dlg.DoModal();
}
