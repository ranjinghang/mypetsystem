
// animalsDlg.h : ͷ�ļ�
//

#pragma once
#include "LinkButton.h"

// CanimalsDlg �Ի���
class CanimalsDlg : public CDialog
{
// ����
public:
	CanimalsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ANIMALS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CLinkButton m_denglu;
	CLinkButton m_zhuce;
	CLinkButton m_youke;
};
