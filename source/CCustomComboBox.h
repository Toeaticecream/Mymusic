#pragma once
#include <afxwin.h>
class CCustomComboBox :public CComboBox
{
	DECLARE_DYNAMIC(CCustomComboBox)

public:
	COLORREF COLOR_BK[3] = { RGB(100, 100, 100), RGB(80, 80, 80), RGB(50, 50, 50) };
	COLORREF COLOR_TEXT[2] = { RGB(200, 200, 200), RGB(150, 150, 180) };
	COLORREF COLOR_BUTTON = RGB(200, 200, 200);
	COLORREF COLOR_LINE = RGB(100, 100, 100);

	CCustomComboBox(COLORREF color_bk0 = RGB(100, 100, 100), COLORREF color_bk1 = RGB(80, 80, 80),
		COLORREF color_bk2 = RGB(50, 50, 50), COLORREF color_text0 = RGB(200, 200, 200), COLORREF color_text1 = RGB(150, 150, 180),
		COLORREF color_button = RGB(200, 200, 200), COLORREF color_line = RGB(100, 100, 100));
	~CCustomComboBox();

	//protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	void OnNcPaint(CDC* pDC);

};
