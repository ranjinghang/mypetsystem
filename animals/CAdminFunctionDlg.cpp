// CAdminFunctionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CAdminFunctionDlg.h"
#include "afxdialogex.h"
#include "CUploadPetDlg.h"
#include "odbcinst.h"


// CAdminFunctionDlg 对话框

IMPLEMENT_DYNAMIC(CAdminFunctionDlg, CDialogEx)

CAdminFunctionDlg::CAdminFunctionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMIN_FUNCTION, pParent)
{

}

CAdminFunctionDlg::~CAdminFunctionDlg()
{
	m_AdoConn.ExitADOConn();
}

void CAdminFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESULT, m_CListCtrlCl);
}


BEGIN_MESSAGE_MAP(CAdminFunctionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CAdminFunctionDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_PLEASE, &CAdminFunctionDlg::OnBnClickedButtonPlease)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CAdminFunctionDlg::OnBnClickedButtonFind)
END_MESSAGE_MAP()


// CAdminFunctionDlg 消息处理程序


void CAdminFunctionDlg::OnBnClickedButtonUpload()
{
	CUploadPetDlg cUploadPetDlg;
	cUploadPetDlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CAdminFunctionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sql;
	int iRec = 0;
	sql.Format("select * from pet where admin_id = '%s'", CMyPublicData::user_id);
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES);
	CMyPublicData::AutoAdjustColumnWidth(&m_CListCtrlCl);
	CString hd[] = { TEXT("宠物名"),TEXT("宠物类型"),TEXT("价格"),TEXT("操作") };
	DWORD dwStyle = m_CListCtrlCl.GetExtendedStyle();
	m_CListCtrlCl.SetExtendedStyle(dwStyle);

	m_CListCtrlCl.SetBkColor(RGB(255, 255, 255));        //设置背景色
	m_CListCtrlCl.SetRowHeigt(30);               //设置行高度
	m_CListCtrlCl.SetHeaderHeight(1.5);          //设置头部高度
	m_CListCtrlCl.SetHeaderFontHW(16, 0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_CListCtrlCl.SetHeaderTextColor(RGB(0, 0, 0)); //设置头部字体颜色
	m_CListCtrlCl.SetTextColor(RGB(0, 0, 0));  //设置文本颜色
	m_CListCtrlCl.SetHeaderBKColor(255, 255, 255, 0); //设置头部背景色
	m_CListCtrlCl.SetFontHW(14, 0);               //设置字体高度，和宽度,0表示缺省宽度
	m_CListCtrlCl.GetHeaderCtrl()->EnableWindow(0); //禁止表头拖动

	for (size_t i = 0; i < 4; i++)
	{
		if (!hd[i].CompareNoCase(_TEXT("操作"))) {
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 100, -1, true);
			continue;
		}
		m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 100);
	}
	int line = 0;
	while (!m_pRs->adoEOF)
	{
		CString m_petId = m_pRs->GetCollect("pet_id");
		CString m_petName = m_pRs->GetCollect("pet_name");
		CString m_petSpecial = m_pRs->GetCollect("pet_special");
		CString m_petPrice = m_pRs->GetCollect("pet_price");
		CString m_adminId = m_pRs->GetCollect("admin_id");

		iRec = m_CListCtrlCl.InsertItem(line, m_petName,line);
		m_CListCtrlCl.SetItemText(line, 0, m_petName);
		m_CListCtrlCl.SetItemText(line, 1, m_petSpecial);
		m_CListCtrlCl.SetItemText(line, 2, m_petPrice);
		m_CListCtrlCl.SetItemBtn(0, TEXT("修改"), line, 3, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_petId);
		line++;
		m_pRs->MoveNext();
	}

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAdminFunctionDlg::OnBnClickedButtonPlease()
{
	m_CListCtrlCl.deleteAll();
	CString sql;
	int iRec = 0;
	sql.Format("select * from jy,dogorder,pet where jy.order_no = dogorder.order_no and dogorder.pet_id = pet.pet_id");
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES);
	CMyPublicData::AutoAdjustColumnWidth(&m_CListCtrlCl);
	CString hd[] = { TEXT("订单名"),TEXT("数量"),TEXT("宠物种类"),TEXT("购买时间"),TEXT("操作") };
	DWORD dwStyle = m_CListCtrlCl.GetExtendedStyle();
	m_CListCtrlCl.SetExtendedStyle(dwStyle);

	m_CListCtrlCl.SetBkColor(RGB(255, 255, 255));        //设置背景色
	m_CListCtrlCl.SetRowHeigt(30);               //设置行高度
	m_CListCtrlCl.SetHeaderHeight(1.5);          //设置头部高度
	m_CListCtrlCl.SetHeaderFontHW(16, 0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_CListCtrlCl.SetHeaderTextColor(RGB(0, 0, 0)); //设置头部字体颜色
	m_CListCtrlCl.SetTextColor(RGB(0, 0, 0));  //设置文本颜色
	m_CListCtrlCl.SetHeaderBKColor(255, 255, 255, 0); //设置头部背景色
	m_CListCtrlCl.SetFontHW(14, 0);               //设置字体高度，和宽度,0表示缺省宽度
	m_CListCtrlCl.GetHeaderCtrl()->EnableWindow(0); //禁止表头拖动

	for (int i = 0; i < 5; i++)
	{
		if (!hd[i].CompareNoCase("操作")) {
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 100, -1, true);
			continue;
		}
		m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 80);
	}
	int line = 0;
	while (!m_pRs->adoEOF)
	{
		CString m_JId = m_pRs->GetCollect("j_id");
		CString m_OrderName = m_pRs->GetCollect("order_name");
		CString m_petSpecial = m_pRs->GetCollect("pet_special");
		CString m_Num = m_pRs->GetCollect("num");
		CString m_CreateTime = m_pRs->GetCollect("create_time");
		_variant_t var = m_pRs->GetCollect("agree");

		iRec = m_CListCtrlCl.InsertItem(line, m_OrderName, line);
		m_CListCtrlCl.SetItemText(line, 0, m_OrderName);
		m_CListCtrlCl.SetItemText(line, 1, m_Num);
		m_CListCtrlCl.SetItemText(line, 2, m_petSpecial);
		m_CListCtrlCl.SetItemText(line, 3, m_CreateTime);
		if (var.vt == VT_NULL) {
			m_CListCtrlCl.SetItemBtn(6, TEXT("同意"), line, 4, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_JId);
		}
		else {
			m_CListCtrlCl.SetItemText(line, 4, _TEXT("已同意"));
		}
		line++;
		m_pRs->MoveNext();
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CAdminFunctionDlg::OnBnClickedButtonFind()
{
	m_CListCtrlCl.deleteAll();
	CString sql;
	int iRec = 0;
	sql.Format("select * from pet where admin_id = '%s'", CMyPublicData::user_id);
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES);
	CMyPublicData::AutoAdjustColumnWidth(&m_CListCtrlCl);
	CString hd[] = { TEXT("宠物名"),TEXT("宠物类型"),TEXT("价格"),TEXT("操作") };
	DWORD dwStyle = m_CListCtrlCl.GetExtendedStyle();
	m_CListCtrlCl.SetExtendedStyle(dwStyle);

	m_CListCtrlCl.SetBkColor(RGB(255, 255, 255));        //设置背景色
	m_CListCtrlCl.SetRowHeigt(30);               //设置行高度
	m_CListCtrlCl.SetHeaderHeight(1.5);          //设置头部高度
	m_CListCtrlCl.SetHeaderFontHW(16, 0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_CListCtrlCl.SetHeaderTextColor(RGB(0, 0, 0)); //设置头部字体颜色
	m_CListCtrlCl.SetTextColor(RGB(0, 0, 0));  //设置文本颜色
	m_CListCtrlCl.SetHeaderBKColor(255, 255, 255, 0); //设置头部背景色
	m_CListCtrlCl.SetFontHW(14, 0);               //设置字体高度，和宽度,0表示缺省宽度
	m_CListCtrlCl.GetHeaderCtrl()->EnableWindow(0); //禁止表头拖动

	for (int i = 0; i < 4; i++)
	{
		if (!hd[i].CompareNoCase("操作")) {
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 100, -1, true);
			continue;
		}
		m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 100);
	}
	int line = 0;
	while (!m_pRs->adoEOF)
	{
		CString m_petId = m_pRs->GetCollect("pet_id");
		CString m_petName = m_pRs->GetCollect("pet_name");
		CString m_petSpecial = m_pRs->GetCollect("pet_special");
		CString m_petPrice = m_pRs->GetCollect("pet_price");
		CString m_adminId = m_pRs->GetCollect("admin_id");

		iRec = m_CListCtrlCl.InsertItem(line, m_petName, line);
		m_CListCtrlCl.SetItemText(line, 0, m_petName);
		m_CListCtrlCl.SetItemText(line, 1, m_petSpecial);
		m_CListCtrlCl.SetItemText(line, 2, m_petPrice);
		m_CListCtrlCl.SetItemBtn(0, TEXT("修改"), line, 3, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_petId);
		line++;
		m_pRs->MoveNext();
	}

	// TODO:  在此添加额外的初始化
	// TODO: 在此添加控件通知处理程序代码
}
