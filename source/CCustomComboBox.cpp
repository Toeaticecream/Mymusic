#include "pch.h"

IMPLEMENT_DYNAMIC(CCustomComboBox, CComboBox)

CCustomComboBox::CCustomComboBox(COLORREF color_bk0, COLORREF color_bk1, COLORREF color_bk2, COLORREF color_text0, COLORREF color_text1, COLORREF color_button, COLORREF color_line):CComboBox()
{
	COLOR_BK[0] = color_bk0;
	COLOR_BK[1] = color_bk1;
	COLOR_BK[2] = color_bk2;
	COLOR_TEXT[0] = color_text0;
	COLOR_TEXT[1] = color_text1;
	COLOR_BUTTON = color_button;
	COLOR_LINE = color_line;
}

CCustomComboBox::~CCustomComboBox()
{

}

void CCustomComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		dc.SetTextColor(COLOR_TEXT[0]);
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, COLOR_BK[0]);
	}

	else if (lpDrawItemStruct->itemState & ODS_FOCUS)
	{
		dc.SetTextColor(COLOR_TEXT[0]);
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, COLOR_BK[0]);
	}
	else
	{
		if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE && lpDrawItemStruct->itemState & ODS_COMBOBOXEDIT)
		{
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, COLOR_BK[2]);
		}
		else
		{
			CRect rect = lpDrawItemStruct->rcItem;
			dc.SetTextColor(COLOR_TEXT[1]);
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, COLOR_BK[2]);
		}
	}
	
	CString sItem;
	if (lpDrawItemStruct->itemID != -1 &&!( lpDrawItemStruct->itemID == GetCount() - 1 && lpDrawItemStruct->itemState & ODS_COMBOBOXEDIT))
	{
		GetLBText(lpDrawItemStruct->itemID, sItem);
		dc.DrawText(sItem, sItem.GetLength(), &lpDrawItemStruct->rcItem,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
	}

	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);
	dc.Detach();

}
BEGIN_MESSAGE_MAP(CCustomComboBox, CComboBox)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CCustomComboBox::OnPaint() 
{
	CPaintDC dc(this);
	OnNcPaint(&dc);
}

void CCustomComboBox::OnNcPaint(CDC* pDC)
{
	CDC MDC;
	MDC.CreateCompatibleDC(pDC);
	MDC.SetMapMode(pDC->GetMapMode());

	CBitmap BMP;
	CRect rc;
	GetClientRect(&rc);

	BMP.CreateCompatibleBitmap(pDC, rc.right - rc.left, rc.bottom - rc.top);
	CBitmap* pOldBmp = MDC.SelectObject(&BMP);
	CPen pen(PS_SOLID, 0, COLOR_LINE);
	CPen* pOldPen = MDC.SelectObject(&pen);

	CBrush bkBrush;
	bkBrush.CreateSolidBrush(COLOR_BK[1]);
	MDC.SelectObject(&bkBrush);
	MDC.Rectangle(rc);

	CRect rcEnd(rc);
	rcEnd.left = rc.right - 20;

	CBrush bkBrushRect;
	bkBrushRect.CreateSolidBrush(COLOR_BK[1]);
	MDC.SelectObject(&bkBrushRect);
	MDC.Rectangle(rcEnd);

	CRgn rgn;
	CPoint ptAngle[3];
	int angleSideWidth = 8;
	ptAngle[0].x = rcEnd.left + rcEnd.Width() / 2 - angleSideWidth / 2;
	ptAngle[0].y = rcEnd.top + rcEnd.Height() / 2 - 2;
	ptAngle[1].x = ptAngle[0].x + angleSideWidth;
	ptAngle[1].y = ptAngle[0].y;
	ptAngle[2].x = rcEnd.left + rcEnd.Width() / 2;
	ptAngle[2].y = ptAngle[0].y + 5;
	CBrush brushAngle;
	rgn.CreatePolygonRgn(ptAngle, 3, ALTERNATE);
	brushAngle.CreateSolidBrush(COLOR_BUTTON); 
	MDC.FillRgn(&rgn, &brushAngle); 
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &MDC, rc.left, rc.top, SRCCOPY);


	MDC.SelectObject(pOldBmp);
	MDC.SelectObject(pOldPen);
	pOldPen->DeleteObject();
	pOldBmp->DeleteObject();
	MDC.DeleteDC();
	bkBrush.DeleteObject();
	bkBrushRect.DeleteObject();
	brushAngle.DeleteObject();
	
}
