#include "stdafx.h"
#include "CMyPublicData.h"

CString CMyPublicData::user_id = "";

void CMyPublicData::AutoAdjustColumnWidth(CListCtrl* pListCtrl) 
{
    pListCtrl->SetRedraw(FALSE);
    CHeaderCtrl* pHeader = pListCtrl->GetHeaderCtrl();
    int nColumnCount = pHeader->GetItemCount();
    for (int i = 0; i < nColumnCount; i++)
    {
        pListCtrl->SetColumnWidth(i, LVSCW_AUTOSIZE);
        int nColumnWidth = pListCtrl->GetColumnWidth(i);
        pListCtrl->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
        int nHeaderWidth = pListCtrl->GetColumnWidth(i);
        pListCtrl->SetColumnWidth(i, max(nColumnWidth, nHeaderWidth) + 5);
    }
    pListCtrl->SetRedraw(TRUE);
}