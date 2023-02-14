#include "pch.h"


CCustomSlider::CCustomSlider()
{
	COLOR_BK = COLORREF(RGB(100,100,100));
	COLOR_RIGHT = COLORREF(RGB(120, 120, 150));
	COLOR_LEFT = COLORREF(RGB(80, 80, 50));
	COLOR_BUTTON_UP = COLORREF(RGB(80,80,100));
	COLOR_BUTTON_ON = COLORREF(RGB(90, 90, 120));
	COLOR_BUTTON_DOWN = COLORREF(RGB(50, 50, 80));

	thumb_down = false;
	thumb_selected = false;
	init_gdi_objs();
}

void CCustomSlider::init_gdi_objs()
{
	pen_thumb_selected.CreatePen(PS_DASHDOTDOT, 2, COLOR_BUTTON_DOWN);
	pen_thumb.CreatePen(PS_DASHDOTDOT, 2, COLOR_BUTTON_UP);
	pen_thumb_on.CreatePen(PS_DASHDOTDOT, 2, COLOR_BUTTON_ON);
	brush_thumb_selected.CreateSolidBrush(COLOR_BUTTON_DOWN);
	brush_thumb.CreateSolidBrush(COLOR_BUTTON_UP);
	brush_thumb_on.CreateSolidBrush(COLOR_BUTTON_ON);
}

void CCustomSlider::delete_gdi_objs()
{
	DeleteObject(pen_thumb_selected);
	DeleteObject(pen_thumb);
	DeleteObject(pen_thumb_on);
	DeleteObject(brush_thumb_selected);
	DeleteObject(brush_thumb);
	DeleteObject(brush_thumb_on);
}

BEGIN_MESSAGE_MAP(CCustomSlider, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CCustomSlider::OnPaint()
{
	CSliderCtrl::OnPaint();
	CDC* pDc = GetDC();
	owner_draw(pDc);
	ReleaseDC(pDc);
}

void CCustomSlider::owner_draw(CDC* pDc)
{
	CRect BKRect;
	GetClientRect(BKRect);
	CRect channelRect;
	GetChannelRect(&channelRect);
	CRect ButtonRect;
	GetThumbRect(ButtonRect);

	pDc->FillSolidRect(BKRect, COLOR_BK);

	pDc->FillSolidRect(channelRect, COLOR_RIGHT);

	CRect leftRect;
	leftRect.left = channelRect.left;
	leftRect.top = channelRect.top;
	leftRect.bottom = channelRect.bottom;
	leftRect.right = ButtonRect.left;

	pDc->FillSolidRect(leftRect, COLOR_LEFT);

	CPen* oldpen;
	CBrush* oldbrush;
	if (thumb_down)
	{
		oldpen = pDc->SelectObject(&pen_thumb_selected);
		oldbrush = pDc->SelectObject(&brush_thumb_selected);
	}
	else  if (!thumb_down && thumb_selected)
	{
		oldpen = pDc->SelectObject(&pen_thumb_on);
		oldbrush = pDc->SelectObject(&brush_thumb_on);
	}
	else
	{
		oldpen = pDc->SelectObject(&pen_thumb);
		oldbrush = pDc->SelectObject(&brush_thumb);
	}
	//get_ellipse_rect(ButtonRect);
	pDc->Rectangle(ButtonRect);
	pDc->SelectObject(oldpen);
	pDc->SelectObject(oldbrush);
}

void CCustomSlider::get_ellipse_rect(CRect& rect)
{
	CPoint center = rect.CenterPoint();
	rect.left = center.x - rect.Width() / 3;
	rect.right = center.x + rect.Width() / 3;
	rect.top = center.y - rect.Height() / 2;
	rect.bottom = center.y + rect.Height() / 2;
}


void CCustomSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect thumbRect;
	GetThumbRect(thumbRect);
	get_ellipse_rect(thumbRect);
	if (thumbRect.PtInRect(point) && !thumb_down)
	{
		thumb_down = TRUE;
		InvalidateRect(thumbRect);
	}
	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CCustomSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	thumb_down = FALSE;
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CCustomSlider::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect thumbRect;
	GetThumbRect(thumbRect);
	get_ellipse_rect(thumbRect);
	BOOL inrect = thumbRect.PtInRect(point);
	if (inrect != thumb_selected)
	{
		thumb_selected = inrect;
		InvalidateRect(thumbRect);
	}
	CSliderCtrl::OnMouseMove(nFlags, point);
}
