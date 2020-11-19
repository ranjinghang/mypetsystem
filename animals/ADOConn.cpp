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
	::CoInitialize(NULL);//初始化OLE/COM库环境(可省)
	try
	{
		m_pCon.CreateInstance("ADODB.Connection");//创建Connection对象
		m_pCon->ConnectionTimeout=3;//设置连接延时
		//m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=..\\data\\animal.mdb","","",adModeUnknown);
		m_pCon->Open("DSN=pet;server=localhost;database=pet", "root", "ran1995129", adModeUnknown);
	}
	catch(_com_error e)//捕获异常
	{
		AfxMessageBox(e.Description());//显示错误信息
	}
}

void ADOConn::ExitADOConn()
{
	if(m_pRs!=NULL)      //先判断记录集是否为空
		m_pRs->Close();  //不为空则先关闭记录集
	m_pCon->Close();     //关闭环境
    ::CoUninitialize();  //释放环境（可省）
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
