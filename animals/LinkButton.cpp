// LinkButton.cpp : implementation file
//

#include "stdafx.h"
#include "animals.h"
#include "LinkButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkButton

CLinkButton::CLinkButton()
{
	bHighlight = bLBtnDown = false;
	hHand = AfxGetApp()->LoadCursor(IDC_CURSOR1);
}

CLinkButton::~CLinkButton()
{
	if (fUnderline.GetSafeHandle()) fUnderline.DeleteObject();
}


BEGIN_MESSAGE_MAP(CLinkButton, CButton)
	//{{AFX_MSG_MAP(CLinkButton)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkButton message handlers

void CLinkButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// ��ȡһ��CDCָ��
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//���尴ť���򲢳�ʼ��
	CRect rect(lpDrawItemStruct->rcItem);

	//���ñ���ģʽ
	COLORREF oc=RGB(30,123,255);
		//oc = pDC->GetTextColor();
int iObk = pDC->SetBkMode(TRANSPARENT);

	//��ʼ����ť״̬
	UINT state = lpDrawItemStruct->itemState;

	CFont * pOldFont = NULL;

	int iYOffset = 0, iXOffset = 0;

	CString strText;
	GetWindowText(strText);

	rect.top  += iYOffset;
	rect.left += iXOffset;


	if (state & ODS_DISABLED)
	{		
		//��ť�ûң�DISABLED��
		CBrush grayBrush;
		grayBrush.CreateSolidBrush (GetSysColor (COLOR_GRAYTEXT));
		CSize sz = pDC->GetTextExtent(strText);
		int x = rect.left + (rect.Width() - sz.cx)/2;
		int y = rect.top + (rect.Height() - sz.cy)/2;
		rect.top  += 2;
		rect.left += 2;
		pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rect.top  -= 2;
		rect.left -= 2;
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		if (bHighlight)//����ڰ�ť��
		{
			if (state & ODS_SELECTED)
			{
				//���°�ť
				pDC->Draw3dRect(rect,RGB(0,0,255), RGB(0,0,255));
			}
			else
			{
				//δ���°�ť
				pDC->Draw3dRect(rect,RGB(255,0,0),RGB(255,0,0));			}
			//������ɫ
			pDC->SetTextColor(RGB(0,0,255));

			//���»��ߣ�Ҳ�������������壩
			if (fUnderline.GetSafeHandle() == NULL)
			{
				CFont * pFont = GetFont();
				ASSERT(pFont);
				LOGFONT lf;
				pFont->GetLogFont(&lf);
				lf.lfUnderline = TRUE;
				fUnderline.CreateFontIndirect(&lf);		
			}

			pOldFont = pDC->SelectObject(&fUnderline);
		}
		else 
		{
			pDC->SetTextColor(RGB(255,123,30));
			pDC->Draw3dRect(rect,RGB(255,0,0),RGB(255,0,0));	}

		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		if (pOldFont) pDC->SelectObject(pOldFont);
	}
}


void CLinkButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	//����һ����ʱ��
	SetTimer(1,10,NULL);
	
	CButton::OnMouseMove(nFlags, point);
}

BOOL CLinkButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (bHighlight) 
	{
		::SetCursor(hHand);
		return true;
	}
	
	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CLinkButton::OnTimer(UINT_PTR nIDEvent)
{
	static bool pPainted = false;
	POINT pt;
	GetCursorPos(&pt);
	CRect rect;
	GetWindowRect (rect);
	if (bLBtnDown)	
	{		
		KillTimer (1);
		if (pPainted) InvalidateRect (NULL);		
		pPainted = FALSE;		
		return;	
	}

	if (!rect.PtInRect (pt))	
	{		
		bHighlight = false;
		KillTimer (1);

		if (pPainted)			
			InvalidateRect(NULL);

		pPainted = false;
		return;	
	}
	else
	{
		bHighlight = true;
		if (!pPainted)
		{
			pPainted = true;
			InvalidateRect(NULL);
		}
	}

	CButton::OnTimer(nIDEvent);
}

int CLinkButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CFont * pFont = GetFont();
	ASSERT(pFont);

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfUnderline = TRUE;

	fUnderline.CreateFontIndirect(&lf);
	
	return 0;
}

void CLinkButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	bLBtnDown = false;
	if (bHighlight)	
	{
		bHighlight = false;
		InvalidateRect(NULL);
	}
	
	CButton::OnLButtonUp(nFlags, point);
}

void CLinkButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	bLBtnDown = true;
	
	CButton::OnLButtonDown(nFlags, point);
}

BOOL CLinkButton::OnEraseBkgnd(CDC* pDC) 
{
	COLORREF cr = GetSysColor(COLOR_3DFACE);
	int r = GetRValue(cr);
	int g = GetGValue(cr);
	int b = GetBValue(cr);
	if (r > 1) r -= 2;
	if (g > 1) g -= 2;
	if (r < 3 && g < 3 && b < 253) b += 2;
	COLORREF cr1 = RGB(255,255,0);
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, cr1);
	
	return CButton::OnEraseBkgnd(pDC);
}
