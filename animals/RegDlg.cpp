// RegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "RegDlg.h"
#include "afxdialogex.h"


// CRegDlg 对话框

IMPLEMENT_DYNAMIC(CRegDlg, CDialogEx)

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegDlg::IDD, pParent)
	, m_answer(_T(""))
	, m_username(_T(""))
	, m_pwd(_T(""))
	, m_pwdrepeat(_T(""))
	, m_questionselect(_T(""))
	, m_age(0)
	, m_city(_T(""))
	, m_phone(_T(""))
	, m_address(_T(""))
{

}

CRegDlg::~CRegDlg()
{
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_question);
	DDX_Text(pDX, IDC_EDIT6, m_answer);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT_address, m_address);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Text(pDX, IDC_EDIT3, m_pwdrepeat);
	DDX_CBString(pDX, IDC_COMBO1, m_questionselect);
	DDX_Text(pDX, IDC_EDIT4, m_age);
	DDX_Text(pDX, IDC_EDIT5, m_city);
	DDX_Control(pDX, IDOK, m_zhuce);
	DDX_Control(pDX, IDC_BUTTON1, m_chongtian);
	DDX_Control(pDX, IDCANCEL, m_quxiao);
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_sexmale, &CRegDlg::OnBnClickedsexmale)
	ON_BN_CLICKED(IDC_sexfemale, &CRegDlg::OnBnClickedsexfemale)
	ON_BN_CLICKED(IDCANCEL, &CRegDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRegDlg 消息处理程序


void CRegDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_username.IsEmpty())
	{
		AfxMessageBox("请输入用户名");
		return;
	}
	if (m_pwd.IsEmpty())
	{
		AfxMessageBox("请输入密码");
		return;
	}
	if (m_pwd != m_pwdrepeat)
	{
		AfxMessageBox("两次输入密码不一致，请重新输入!");
		return;
	}
	if (m_address.IsEmpty()) {
		CString message("地址不能为空");
		AfxMessageBox(message);
	}
	if (m_phone.IsEmpty()) {
		CString message("电话不能为空");
		AfxMessageBox(message);
	}
	if (m_question.GetCurSel() == -1)
	{
		AfxMessageBox("请选择密码提示问题");
		return;
	}
	if (m_answer.IsEmpty())
	{
		AfxMessageBox("请输入提示问题的答案");
		return;
	}

	CString strquestion;
	m_question.GetLBText(m_question.GetCurSel(), strquestion);
	CString sex;
	if (m_radio == 0)
		sex.Format("");
	if (m_radio == 1)
		sex.Format("男");
	if (m_radio == 2)
		sex.Format("女");
	CTime time;
	time = CTime::GetCurrentTime();//当前系统时间
	CString nowtime = time.Format("%Y-%m-%d");

	try
	{
		m_AdoConn.OnInitADOConn();
		CString sql = "select*from login where user_id='" + m_username + "'";
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		if (!m_pRs->adoEOF)
		{
			AfxMessageBox(_TEXT("用户名已存在"));
			return;
		}
		else
		{
			if (((CButton*)GetDlgItem(IDC_RADIO_ADMIN_CHECK))->GetCheck()) {
				type = "admin";
			}
			else {
				type = "user";
			}
			//向数据库插入数据，完成注册工作！
			sql.Format("insert into login(user_id,pw,question,answer,sex,age,city,register_date,address,phone,type)values('%s','%s','%s','%s','%s',%d,'%s','%s','%s','%s','%s')",
				m_username, m_pwd, strquestion, m_answer,sex,m_age, m_city, nowtime,m_address,m_phone,type);

			m_AdoConn.ExecuteSQL((_bstr_t)sql);
			m_AdoConn.ExitADOConn();
			AfxMessageBox("注册成功");
			CDialog::OnCancel();

		}
	}
	catch (...)
	{
		AfxMessageBox("操作失败");
		return;
	}
}


BOOL CRegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_questionselect = "请选择一个问题";
	UpdateData(false);//使显示
	m_question.AddString("你的父亲生日是哪天？");//向组合框中添加信息
	m_question.AddString("你的母亲生日是哪天？");
	m_question.AddString("你的女朋友的是谁？");
	m_question.AddString("你家养的猫叫什么？");
	m_question.AddString("你的手机号码的后三位是什么？");
	m_question.AddString("你的大学班主任姓名？");
	m_question.AddString("最难忘的一件事是什么？");
	m_question.AddString("最喜欢的运动是？");
	m_question.AddString("最喜欢的歌曲是？");
	((CButton*)GetDlgItem(IDC_sexmale))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_ADMIN_CHECK))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CRegDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_username = "";
	m_pwd = "";
	m_pwdrepeat = "";
	m_address = "";
	m_phone = "";
	m_question.SetCurSel(0);
	m_answer = "";
	m_age = NULL;
	m_city = "";

	CButton* radio3 = (CButton*)GetDlgItem(IDC_sexmale);
	CButton* radio4 = (CButton*)GetDlgItem(IDC_sexfemale);
	radio3->SetCheck(0);
	radio4->SetCheck(0);
	CButton* radioAdmin = (CButton*)GetDlgItem(IDC_RADIO_ADMIN_CHECK);
	CButton* radioUser = (CButton*)GetDlgItem(IDC_RADIO_USER_CHECK);
	radioAdmin->SetCheck(0);
	radioUser->SetCheck(0);

	UpdateData(FALSE);
}


void CRegDlg::OnBnClickedsexmale()
{
	// TODO:  在此添加控件通知处理程序代码
	m_radio = 1;//选择性别为男
}


void CRegDlg::OnBnClickedsexfemale()
{
	// TODO:  在此添加控件通知处理程序代码
	m_radio = 2;//选择性别为女
}


void CRegDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CRegDlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
