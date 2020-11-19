#pragma once


// CHeaderCtrlCl

class CHeaderCtrlCl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CHeaderCtrlCl)

public:
	CHeaderCtrlCl();
	virtual ~CHeaderCtrlCl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CStringArray m_HChar;
	CString m_Format;
public:
	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;	// �����屳��������ϵ��
	float m_Height;  //��ͷ�߶ȣ����Ǳ���,
	int m_fontHeight; //����߶�
	int m_fontWith;   //������
	COLORREF m_color;
	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);

};


