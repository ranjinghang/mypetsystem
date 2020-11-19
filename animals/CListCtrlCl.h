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
	// �и�
	int m_nRowHeight;
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, bool nCreatBtn = false);//�Ƿ񴴽���ť
public:
	// Gradient - ����ϵ�������屳����,���ý�����Ϊ0
	void SetHeaderBKColor(int R, int G, int B, int Gradient);
public:
	// ���ñ�ͷ�߶�
	void SetHeaderHeight(float Height);
	CPtrList m_ptrListCol;  //��������ɫ
	CPtrList m_ptrListItem; //����Item��ɫ��
	CPtrList m_colTextColor; //������������ɫ
	CPtrList m_ItemTextColor; //���浥Ԫ��������ɫ
	bool FindColColor(int col, COLORREF& color); //��������ɫ
	bool FindItemColor(int col, int row, COLORREF& color);
	bool FindColTextColor(int col, COLORREF& color); //������������ɫ
	bool FindItemTextColor(int col, int row, COLORREF& color);
	void SetColColor(int col, COLORREF color);  //��������ɫ
	void SetItemColor(int col, int row, COLORREF color); //����Item��ɫ
	void SetColTextColor(int col, COLORREF color);   //�������ı���ɫ
	void SetItemTextColor(int col, int row, COLORREF color);
	void SetRowHeigt(int nHeight); //�����и�
	void SetHeaderFontHW(int nHeight, int nWith); //���ñ�ͷ�����С
	void SetHeaderTextColor(COLORREF color);
	COLORREF m_color;
	BOOL SetTextColor(COLORREF cr);
	void SetFontHW(int nHeight, int nWith);  //��������ĸߺͿ�
public:
	// ����߶�
	int m_fontHeight;
public:
	// ������
	int m_fontWith;
public:
	int m_nCreatBtnCol;

public://���ڰ�ť���
	vector<m_BtnGroup> m_BtVect;
	void SetItemBtn(int type, CString text,int nItem, int nSubItem, HWND hMain, CString id);
	void deleteAll();
};


