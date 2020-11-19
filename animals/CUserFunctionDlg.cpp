// CUserFunctionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CUserFunctionDlg.h"
#include "afxdialogex.h"


// CUserFunctionDlg 对话框

IMPLEMENT_DYNAMIC(CUserFunctionDlg, CDialogEx)

CUserFunctionDlg::CUserFunctionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_USER_FUNCTION, pParent)
{

}

CUserFunctionDlg::~CUserFunctionDlg()
{
	m_AdoConn.ExitADOConn();

}

void CUserFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESULT, m_CListCtrlCl);
}


BEGIN_MESSAGE_MAP(CUserFunctionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PET_LIST, &CUserFunctionDlg::OnBnClickedButtonPetList)
	ON_BN_CLICKED(IDC_BUTTON_ORDER, &CUserFunctionDlg::OnBnClickedButtonOrder)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_JIYANG, &CUserFunctionDlg::OnBnClickedButtonJiyang)
END_MESSAGE_MAP()


// CUserFunctionDlg 消息处理程序


BOOL CUserFunctionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_flag = true;
	CString sql;
	int iRec = 0;
	sql.Format("select * from pet");
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
		m_CListCtrlCl.SetItemBtn(1, TEXT("购买"), line, 3, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_petId);
		line++;
		m_pRs->MoveNext();
	}

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserFunctionDlg::OnBnClickedButtonPetList()
{
	m_CListCtrlCl.deleteAll();
	CString sql;
	int iRec = 0;
	sql.Format("select * from pet");
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
		m_CListCtrlCl.SetItemBtn(1, TEXT("购买"), line, 3, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_petId);
		line++;
		m_pRs->MoveNext();
	}

	// TODO: 在此添加控件通知处理程序代码
}


void CUserFunctionDlg::OnBnClickedButtonOrder()
{
	m_flag = true;
	m_CListCtrlCl.deleteAll();
	// TODO: 在此添加控件通知处理程序代码
	CString sql;
	int iRec = 0;
	sql.Format("select * from dogorder as d, pet as p where d.pet_id = p.pet_id and user_id = '");
	sql.Append(CMyPublicData::user_id);
	sql.AppendChar('\'');
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES);
	CMyPublicData::AutoAdjustColumnWidth(&m_CListCtrlCl);
	CString hd[] = { TEXT("订单名称"),TEXT("宠物名称"),TEXT("购买数量"),TEXT("购买时间"),TEXT("操作") };
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

	for (size_t i = 0; i < 5; i++)
	{
		if (!hd[i].CompareNoCase("操作")) {
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 45, -1, true);
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 45, -1, true);
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 45, -1, true);
			continue;
		}
		m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 80);
	}
	int line = 0;
	while (!m_pRs->adoEOF)
	{
		CString m_orderId = m_pRs->GetCollect("order_no");
		CString m_orderName = m_pRs->GetCollect("order_name");
		CString m_petName = m_pRs->GetCollect("pet_Name");
		CString m_num = m_pRs->GetCollect("num");
		CString m_CreateTime = m_pRs->GetCollect("create_time");
		CString m_Evaluate = m_pRs->GetCollect("evaluate");

		iRec = m_CListCtrlCl.InsertItem(line, m_orderName, line);
		m_CListCtrlCl.SetItemText(line, 0, m_orderName);
		m_CListCtrlCl.SetItemText(line, 1, m_petName);
		m_CListCtrlCl.SetItemText(line, 2, m_num);
		m_CListCtrlCl.SetItemText(line, 3, m_CreateTime);
		
		m_CListCtrlCl.SetItemBtn(4, TEXT("售后"), line, 5, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_orderId);
		if (m_Evaluate.IsEmpty()) {
			m_CListCtrlCl.SetItemBtn(2, TEXT("评价"), line, 6, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_orderId);
		}
		else {
			m_CListCtrlCl.SetItemBtn(3, TEXT("详情"), line, 4, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_orderId);
		}
		line++;
		m_pRs->MoveNext();
	}
}


void CUserFunctionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


void CUserFunctionDlg::OnBnClickedButtonJiyang()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CListCtrlCl.deleteAll();
	// TODO: 在此添加控件通知处理程序代码
	CString sql;
	int iRec = 0;
	sql.Format("select d.order_no, p.pet_name, d.create_time, j.j_id, j.agree from dogorder as d join pet as p on d.pet_id = p.pet_id left join jy as j on d.order_no = j.order_no where user_id = '");
	sql.Append(CMyPublicData::user_id);
	sql.AppendChar('\'');
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES);
	CMyPublicData::AutoAdjustColumnWidth(&m_CListCtrlCl);
	CString hd[] = { TEXT("宠物名称"),TEXT("购买时间"),TEXT("状态"),TEXT("操作") };
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
			m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 95, -1, true);
			continue;
		}
		m_CListCtrlCl.InsertColumn(i, hd[i], LVCFMT_CENTER, 120);
	}
	int line = 0;
	while (!m_pRs->adoEOF)
	{
		CString m_orderId = m_pRs->GetCollect("order_no");
		CString m_petName = m_pRs->GetCollect("pet_Name");
		CString m_CreateTime = m_pRs->GetCollect("create_time");
		_variant_t var = m_pRs->GetCollect("j_id");
		_variant_t varAgree = m_pRs->GetCollect("agree");

		iRec = m_CListCtrlCl.InsertItem(line, m_petName, line);
		m_CListCtrlCl.SetItemText(line, 0, m_petName);
		m_CListCtrlCl.SetItemText(line, 1, m_CreateTime);

		CString status;
		if (var.vt == VT_NULL) {
			m_CListCtrlCl.SetItemBtn(5, TEXT("申请寄养"), line, 3, GetDlgItem(IDC_LIST_RESULT)->m_hWnd, m_orderId);
			status.Append(_TEXT("未寄养"));
		}
		else {
			if (varAgree.vt == VT_NULL) {
				status.Append(_TEXT("等待管理员同意"));
			}
			else {
				status.Append(_TEXT("已寄养"));
			}
		}
		m_CListCtrlCl.SetItemText(line, 2, status);

		line++;
		m_pRs->MoveNext();
	}
}
