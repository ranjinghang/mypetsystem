// RegDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "animals.h"
#include "RegDlg.h"
#include "afxdialogex.h"


// CRegDlg �Ի���

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


// CRegDlg ��Ϣ�������


void CRegDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_username.IsEmpty())
	{
		AfxMessageBox("�������û���");
		return;
	}
	if (m_pwd.IsEmpty())
	{
		AfxMessageBox("����������");
		return;
	}
	if (m_pwd != m_pwdrepeat)
	{
		AfxMessageBox("�����������벻һ�£�����������!");
		return;
	}
	if (m_address.IsEmpty()) {
		CString message("��ַ����Ϊ��");
		AfxMessageBox(message);
	}
	if (m_phone.IsEmpty()) {
		CString message("�绰����Ϊ��");
		AfxMessageBox(message);
	}
	if (m_question.GetCurSel() == -1)
	{
		AfxMessageBox("��ѡ��������ʾ����");
		return;
	}
	if (m_answer.IsEmpty())
	{
		AfxMessageBox("��������ʾ����Ĵ�");
		return;
	}

	CString strquestion;
	m_question.GetLBText(m_question.GetCurSel(), strquestion);
	CString sex;
	if (m_radio == 0)
		sex.Format("");
	if (m_radio == 1)
		sex.Format("��");
	if (m_radio == 2)
		sex.Format("Ů");
	CTime time;
	time = CTime::GetCurrentTime();//��ǰϵͳʱ��
	CString nowtime = time.Format("%Y-%m-%d");

	try
	{
		m_AdoConn.OnInitADOConn();
		CString sql = "select*from login where user_id='" + m_username + "'";
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		if (!m_pRs->adoEOF)
		{
			AfxMessageBox(_TEXT("�û����Ѵ���"));
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
			//�����ݿ�������ݣ����ע�Ṥ����
			sql.Format("insert into login(user_id,pw,question,answer,sex,age,city,register_date,address,phone,type)values('%s','%s','%s','%s','%s',%d,'%s','%s','%s','%s','%s')",
				m_username, m_pwd, strquestion, m_answer,sex,m_age, m_city, nowtime,m_address,m_phone,type);

			m_AdoConn.ExecuteSQL((_bstr_t)sql);
			m_AdoConn.ExitADOConn();
			AfxMessageBox("ע��ɹ�");
			CDialog::OnCancel();

		}
	}
	catch (...)
	{
		AfxMessageBox("����ʧ��");
		return;
	}
}


BOOL CRegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_questionselect = "��ѡ��һ������";
	UpdateData(false);//ʹ��ʾ
	m_question.AddString("��ĸ������������죿");//����Ͽ��������Ϣ
	m_question.AddString("���ĸ�����������죿");
	m_question.AddString("���Ů���ѵ���˭��");
	m_question.AddString("�������è��ʲô��");
	m_question.AddString("����ֻ�����ĺ���λ��ʲô��");
	m_question.AddString("��Ĵ�ѧ������������");
	m_question.AddString("��������һ������ʲô��");
	m_question.AddString("��ϲ�����˶��ǣ�");
	m_question.AddString("��ϲ���ĸ����ǣ�");
	((CButton*)GetDlgItem(IDC_sexmale))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_ADMIN_CHECK))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CRegDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_radio = 1;//ѡ���Ա�Ϊ��
}


void CRegDlg::OnBnClickedsexfemale()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_radio = 2;//ѡ���Ա�ΪŮ
}


void CRegDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CRegDlg::OnEnChangeEdit10()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
