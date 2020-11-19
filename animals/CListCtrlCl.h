#pragma once


#include "CHeaderCtrlCl.h"
#include "CListCtrlUpdateButton.h"
#include <vector>
using namespace std;

typedef struct BTNGROUP
{
	CListCtrlUpdateButton* m_Btn[2];
	BTNGROUP()
	{
		m_Btn[0] = NULL;
		m_Btn[1] = NULL;
	}
}m_BtnGroup;


// CListCtrlCl

class CListCtrlCl : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlCl)

public:
	CHeaderCtrlCl m_Header;
	CListCtrlCl();
	virtual ~CListCtrlCl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	// 行高
	int m_nRowHeight;
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, bool nCreatBtn = false);//是否创建按钮
public:
	// Gradient - 渐变系数，立体背景用,不用渐变设为0
	void SetHeaderBKColor(int R, int G, int B, int Gradient);
public:
	// 设置表头高度
	void SetHeaderHeight(float Height);
	CPtrList m_ptrListCol;  //保存列颜色
	CPtrList m_ptrListItem; //保存Item颜色表
	CPtrList m_colTextColor; //保存列字体颜色
	CPtrList m_ItemTextColor; //保存单元格字体颜色
	bool FindColColor(int col, COLORREF& color); //查找列颜色
	bool FindItemColor(int col, int row, COLORREF& color);
	bool FindColTextColor(int col, COLORREF& color); //查找列字体颜色
	bool FindItemTextColor(int col, int row, COLORREF& color);
	void SetColColor(int col, COLORREF color);  //设置列颜色
	void SetItemColor(int col, int row, COLORREF color); //设置Item颜色
	void SetColTextColor(int col, COLORREF color);   //设置列文本颜色
	void SetItemTextColor(int col, int row, COLORREF color);
	void SetRowHeigt(int nHeight); //设置行高
	void SetHeaderFontHW(int nHeight, int nWith); //设置表头字体大小
	void SetHeaderTextColor(COLORREF color);
	COLORREF m_color;
	BOOL SetTextColor(COLORREF cr);
	void SetFontHW(int nHeight, int nWith);  //设置字体的高和宽
public:
	// 字体高度
	int m_fontHeight;
public:
	// 字体宽度
	int m_fontWith;
public:
	int m_nCreatBtnCol;

public://用于按钮添加
	vector<m_BtnGroup> m_BtVect;
	void SetItemBtn(int type, CString text,int nItem, int nSubItem, HWND hMain, CString id);
	void deleteAll();
};


