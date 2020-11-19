#if !defined(AFX_LINKBUTTON_H__37D871C6_C673_11D3_B3A5_001088028526__INCLUDED_)
#define AFX_LINKBUTTON_H__37D871C6_C673_11D3_B3A5_001088028526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinkButton window

class CLinkButton : public CButton
{
// Construction
public:
	CLinkButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFont fUnderline;
	HCURSOR hHand;
	bool bLBtnDown;
	bool bHighlight;
	virtual ~CLinkButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLinkButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKBUTTON_H__37D871C6_C673_11D3_B3A5_001088028526__INCLUDED_)
