// CListCtrlCl.cpp: 实现文件
//

#include "stdafx.h"
#include "animals.h"
#include "CListCtrlCl.h"

struct stColor
{
	int nRow;
	int nCol;
	COLORREF rgb;
};

// CListCtrlCl

IMPLEMENT_DYNAMIC(CListCtrlCl, CLinkCtrl)

CListCtrlCl::CListCtrlCl()
	: m_nRowHeight(0)
	, m_fontHeight(12)
	, m_fontWith(0)
{
	m_color = RGB(0, 0, 0);
}

CListCtrlCl::~CListCtrlCl()
{
	for each (auto var in m_BtVect)//内存释放清理
	{
		var.m_Btn[0]->DestroyWindow();
		delete var.m_Btn[0];
	}
	m_BtVect.clear();
	vector<m_BtnGroup>().swap(m_BtVect);
}

BEGIN_MESSAGE_MAP(CListCtrlCl, CLinkCtrl)
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

//是否创建按钮
int CListCtrlCl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */, bool nCreatBtn)
{
	m_Header.m_HChar.Add(lpszColumnHeading);
	if (nFormat == LVCFMT_LEFT)
	{
		m_Header.m_Format.AppendFormat("%ld", L"0");
	}
	else if (nFormat == LVCFMT_CENTER)
	{
		m_Header.m_Format.AppendFormat("%ld", L"1");
	}
	else if (nFormat == LVCFMT_RIGHT)
	{
		m_Header.m_Format.AppendFormat("%ld", L"0");
	}
	else
	{
		m_Header.m_Format.AppendFormat("%ld", L"1");
	}
	if (nCreatBtn)
	{
		m_nCreatBtnCol = nCol;//记录创建按钮的列
	}
	return CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
}
// Gradient - 渐变系数，立体背景用,不用渐变设为0
void CListCtrlCl::SetHeaderBKColor(int R, int G, int B, int Gradient) //设置表头背景色
{
	m_Header.m_R = R;
	m_Header.m_G = G;
	m_Header.m_B = B;
	m_Header.m_Gradient = Gradient;
}

// 设置表头高度
void CListCtrlCl::SetHeaderHeight(float Height) //设置表头高度
{
	m_Header.m_Height = Height;
}
bool CListCtrlCl::FindColColor(int col, COLORREF& color) //查找列颜色
{
	int flag = 0;
	for (POSITION pos = m_ptrListCol.GetHeadPosition(); pos != NULL;)
	{
		stColor* pColor = (stColor*)m_ptrListCol.GetNext(pos);
		if (pColor->nCol == col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1 == flag)
	{
		return true;
	}
	return false;
}
bool CListCtrlCl::FindItemColor(int col, int row, COLORREF& color) //查找颜色
{
	int flag = 0;
	for (POSITION pos = m_ptrListItem.GetHeadPosition(); pos != NULL;)
	{
		stColor* pColor = (stColor*)m_ptrListItem.GetNext(pos);
		if (pColor->nCol == col && pColor->nRow == row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1 == flag)
	{
		return true;
	}
	return false;
}
void CListCtrlCl::SetColColor(int col, COLORREF color) //设置列颜色
{
	stColor* pColor = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_ptrListCol.AddTail(pColor);
}
void CListCtrlCl::SetItemColor(int col, int row, COLORREF color) //设置格子颜色
{
	stColor* pColor = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ptrListItem.AddTail(pColor);
}
void CListCtrlCl::SetRowHeigt(int nHeight) //高置行高
{
	m_nRowHeight = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
void CListCtrlCl::SetHeaderFontHW(int nHeight, int nWith) //设置头部字体宽和高
{
	m_Header.m_fontHeight = nHeight;
	m_Header.m_fontWith = nWith;
}
void CListCtrlCl::SetHeaderTextColor(COLORREF color) //设置头部字体颜色
{
	m_Header.m_color = color;
}
BOOL CListCtrlCl::SetTextColor(COLORREF cr)  //设置字体颜色
{
	m_color = cr;
	return TRUE;
}
void CListCtrlCl::SetFontHW(int nHeight, int nWith) //设置字体高和宽
{
	m_fontHeight = nHeight;
	m_fontWith = nWith;
}
void CListCtrlCl::SetColTextColor(int col, COLORREF color)
{
	stColor* pColor = new stColor;
	pColor->nCol = col;
	pColor->rgb = color;
	m_colTextColor.AddTail(pColor);
}
bool CListCtrlCl::FindColTextColor(int col, COLORREF& color)
{
	int flag = 0;
	for (POSITION pos = m_colTextColor.GetHeadPosition(); pos != NULL;)
	{
		stColor* pColor = (stColor*)m_colTextColor.GetNext(pos);
		if (pColor->nCol == col)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1 == flag)
	{
		return true;
	}
	return false;
}
bool CListCtrlCl::FindItemTextColor(int col, int row, COLORREF& color)
{
	int flag = 0;
	for (POSITION pos = m_ItemTextColor.GetHeadPosition(); pos != NULL;)
	{
		stColor* pColor = (stColor*)m_ItemTextColor.GetNext(pos);
		if (pColor->nCol == col && pColor->nRow == row)
		{
			flag = 1;
			color = pColor->rgb;
			break;
		}
	}
	if (1 == flag)
	{
		return true;
	}
	return false;
}
void CListCtrlCl::SetItemTextColor(int col, int row, COLORREF color)
{
	stColor* pColor = new stColor;
	pColor->nCol = col;
	pColor->nRow = row;
	pColor->rgb = color;
	m_ItemTextColor.AddTail(pColor);
}

static int m_StaticBtId = 0;
void CListCtrlCl::SetItemBtn(int type, CString text, int nItem, int nSubItem, HWND hMain, CString id)
{
	CRect rect;
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_OWNERDRAW;
	m_BtnGroup m_Group;
	m_Group.m_Btn[0] = new CListCtrlUpdateButton(type, nItem, nSubItem, rect, hMain,id);
	m_Group.m_Btn[0]->Create(text, dwStyle, rect, this, m_StaticBtId);

	m_BtVect.push_back(m_Group);
	return;

}

void CListCtrlCl::deleteAll()
{
	DeleteAllItems();
	int m_ColumnNum = GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < m_ColumnNum; i++) 
	{
		DeleteColumn(0);
	}
	for each (auto var in m_BtVect)//内存释放清理
	{
		var.m_Btn[0]->DestroyWindow();
		delete var.m_Btn[0];
	}
	m_BtVect.clear();
	vector<m_BtnGroup>().swap(m_BtVect);
}

/*	//获取选中行列
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	this->ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nColSelected, nRowSelected;
	int nItem = SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		nColSelected = lvinfo.iItem; //行
		nRowSelected = lvinfo.iSubItem; //列
		}*/


// CListCtrlCl 消息处理程序


