#include "stdafx.h"
#include "CListCtrlUpdateButton.h"
#include "CUpdatePetDlg.h"
#include "CBuyDog.h"
#include "CEVADlg.h"
#include "CEvaDetailDlg.h"

IMPLEMENT_DYNAMIC(CListCtrlUpdateButton, CButton)

CListCtrlUpdateButton::CListCtrlUpdateButton()
{
}


CListCtrlUpdateButton::CListCtrlUpdateButton(int type,int nItem, int nSubItem, CRect rect, HWND hParent, CString id)    //-
{
	m_type = type;
	m_inItem = nItem;
	m_inSubItem = nSubItem;
	m_rect = rect;
	m_hParent = hParent;
	bEnable = TRUE;
	m_id = id;
}

CListCtrlUpdateButton::~CListCtrlUpdateButton() {

}

BEGIN_MESSAGE_MAP(CListCtrlUpdateButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED,&CListCtrlUpdateButton::OnBnClicked)
END_MESSAGE_MAP()

void CListCtrlUpdateButton::OnBnClicked()
{
	CString message("操作成功");
	// TODO: 在此添加控件通知处理程序代码
	// type 0:修改更新,1:购买,2:评价3:详情4:售后5:申请寄养6:同意
	if (m_type == 0) 
	{
		CUpdatePetDlg cUpdatePetdlg;
		cUpdatePetdlg.m_petId = m_id;
		cUpdatePetdlg.DoModal();
	}
	else if (m_type == 1) 
	{
		CBuyDog cBuy;
		cBuy.m_dog_id = m_id;
		cBuy.DoModal();
	}
	else if (m_type == 2) {
		CEVADlg cEva;
		cEva.m_orderNo = m_id;
		cEva.DoModal();
	}
	else if (m_type == 3) {
		CEvaDetailDlg cEvaD;
		cEvaD.m_orderNo = m_id;
		cEvaD.DoModal();
	}
	else if (m_type == 4) {
		CString sql;
		sql.Format("delete from dogorder where order_no = %d", atoi(m_id));
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		AfxMessageBox(message);
	}
	else if (m_type == 5) {
		CString sql;
		sql.Format("insert into jy (order_no, `status`) values ('%s',%d)",m_id, 0);
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		AfxMessageBox(message);
	}
	else if (m_type == 6) {
		CString sql;
		sql.Format("update jy set agree = %d", 1);
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		AfxMessageBox(message);
	}
	
}

void CListCtrlUpdateButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct);

	//以下为常态按钮绘制
	//TRACE("* Drawing: %08x\n", lpDrawItemStruct->itemState);
	CString sCaption;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);	// get device context
	RECT r = lpDrawItemStruct->rcItem;					// context rectangle
	int cx = r.right - r.left;						// get width
	int cy = r.bottom - r.top;						// get height
	// get text box position
	RECT tr = { r.left + 2, r.top, r.right - 2, r.bottom };

	GetWindowText(sCaption);							// get button text
	pDC->SetBkMode(TRANSPARENT);

	// Select the correct skin 
	if (lpDrawItemStruct->itemState & ODS_DISABLED)//鼠标禁用
	{
		// no skin selected for disabled state -> standard button 
		pDC->FillSolidRect(&r, GetSysColor(COLOR_BTNFACE));

		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));//)m_TextColor灰色字体  文字偏移
		OffsetRect(&tr, -1, -1);
		pDC->DrawText(sCaption, &tr, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else
	{										// SELECTED (DOWN) BUTTON
		if ((lpDrawItemStruct->itemState & ODS_SELECTED))//当按下按钮时的处理
		{
			// no skin selected for selected state -> standard buttonRGB(255,152,0)
			pDC->FillSolidRect(&r, RGB(39, 169, 241));//GetSysColor(COLOR_BTNFACE)

		}
		else
		{											// DEFAULT BUTTON
			pDC->FillSolidRect(&r, GetSysColor(COLOR_BTNFACE));//
		}
		// paint the enabled button text
		//pDC->SetTextColor(RGB(255,255,255));
		CFont nFont, * nOldFont;
		nFont.CreatePointFont(90, _T("微软雅黑"));//创建字体 
		nOldFont = pDC->SelectObject(&nFont);

		DrawText(lpDrawItemStruct->hDC, sCaption, sCaption.GetLength(), &tr, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		pDC->SelectStockObject(SYSTEM_FONT);
		//pDC->DrawText(sCaption, &tr, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
}