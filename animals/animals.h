
// animals.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"
#include "CMyPublicData.h"


// CanimalsApp: 
// �йش����ʵ�֣������ animals.cpp
//

class CanimalsApp : public CWinApp
{
public:
	CanimalsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CanimalsApp theApp;