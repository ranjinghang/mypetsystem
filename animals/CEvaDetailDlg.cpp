// CEvaDetailDlg.cpp: 实现文件
//
#include "stdafx.h"
#include "animals.h"
#include "CEvaDetailDlg.h"
#include "afxdialogex.h"


// CEvaDetailDlg 对话框

IMPLEMENT_DYNAMIC(CEvaDetailDlg, CDialogEx)

CEvaDetailDlg::CEvaDetailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EVA_DETAIL, pParent)
	, m_orderNo(_T(""))
{

}

CEvaDetailDlg::~CEvaDetailDlg()
{
}

void CEvaDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EVALUATE, m_EditEva);
	DDX_Control(pDX, IDC_EDIT_ORDER_NO, m_EditOrderNo);
}


BEGIN_MESSAGE_MAP(CEvaDetailDlg, CDialogEx)
END_MESSAGE_MAP()



// CEvaDetailDlg 消息处理程序


BOOL CEvaDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString sql;
	sql.Format("select * from dogorder where order_no = '%s'", m_orderNo);
	m_AdoConn.OnInitADOConn();
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
	m_EditOrderNo.SetWindowTextA(m_orderNo);
	
	if (!m_pRs->adoEOF) {
		CString m_Eval = m_pRs->GetCollect("evaluate");
		m_EditEva.SetWindowTextA(m_Eval);
	}

	m_AdoConn.ExitADOConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
