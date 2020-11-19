#pragma once

#include "ADOConn.h"

class CListCtrlUpdateButton :
    public CButton
{
	DECLARE_DYNAMIC(CListCtrlUpdateButton)
public:
    CListCtrlUpdateButton();
    CListCtrlUpdateButton(int type, int nItem, int nSubItem, CRect rect, HWND hParent, CString id);
    ~CListCtrlUpdateButton();
protected:
    DECLARE_MESSAGE_MAP()
public:
    CString m_petId;

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClicked();
	int m_inItem;
	int m_inSubItem;
	CRect m_rect;
	HWND m_hParent;
	BOOL bEnable;
	int m_type;
	CString m_id;
	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;
};

