// CBuyDog.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CBuyDog.h"
#include "afxdialogex.h"


// CBuyDog 对话框

IMPLEMENT_DYNAMIC(CBuyDog, CDialogEx)

CBuyDog::CBuyDog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BUY_DOG, pParent)
	, m_amount(_T(""))
{
	

}

CBuyDog::~CBuyDog()
{

}

void CBuyDog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_amount);
}


BEGIN_MESSAGE_MAP(CBuyDog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBuyDog::OnBnClickedOk)
END_MESSAGE_MAP()


// CBuyDog 消息处理程序


void CBuyDog::OnBnClickedOk()
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
	sql.Format("insert into dogorder( order_name, user_id, pet_id, create_time, num, evaluate)values('%s', '%s', '%s', '%s', %d, '')", "购买订单", CMyPublicData::user_id, m_dog_id, nowtime , atoi(m_amount));
	m_AdoConn.ExecuteSQL((_bstr_t)sql);
	m_AdoConn.ExitADOConn();
	CString message("购买成功");
	AfxMessageBox(message);

	CDialogEx::OnOK();
}



BOOL CBuyDog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_PET_INFO)->SetWindowTextA(m_dog_id);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
