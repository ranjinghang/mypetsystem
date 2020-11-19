// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "animals.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{
	
}

ADOConn::~ADOConn()
{
	
}

void ADOConn::OnInitADOConn()
{
	::CoInitialize(NULL);//��ʼ��OLE/COM�⻷��(��ʡ)
	try
	{
		m_pCon.CreateInstance("ADODB.Connection");//����Connection����
		m_pCon->ConnectionTimeout=3;//����������ʱ
		//m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=..\\data\\animal.mdb","","",adModeUnknown);
		m_pCon->Open("DSN=pet;server=localhost;database=pet", "root", "ran1995129", adModeUnknown);
	}
	catch(_com_error e)//�����쳣
	{
		AfxMessageBox(e.Description());//��ʾ������Ϣ
	}
}

void ADOConn::ExitADOConn()
{
	if(m_pRs!=NULL)      //���жϼ�¼���Ƿ�Ϊ��
		m_pRs->Close();  //��Ϊ�����ȹرռ�¼��
	m_pCon->Close();     //�رջ���
    ::CoUninitialize();  //�ͷŻ�������ʡ��
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();
		m_pRs.CreateInstance("ADODB.Recordset");
		m_pRs->Open(bstrSQL,m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRs;
	
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();
		m_pCon->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}
}
