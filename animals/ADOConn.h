// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__97FBB874_3C69_4570_8E21_2BDEB844E9E5__INCLUDED_)
#define AFX_ADOCONN_H__97FBB874_3C69_4570_8E21_2BDEB844E9E5__INCLUDED_

//���붯̬���ݿ�
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF", "adoEOF")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ADOConn  
{
public:
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	void ExitADOConn();
	void OnInitADOConn();
	ADOConn();
	virtual ~ADOConn();
	_ConnectionPtr m_pCon;//���һ��ָ��Connection�����ָ��
	_RecordsetPtr m_pRs;  //���һ��ָ��Recordset�����ָ��

};

#endif // !defined(AFX_ADOCONN_H__97FBB874_3C69_4570_8E21_2BDEB844E9E5__INCLUDED_)
