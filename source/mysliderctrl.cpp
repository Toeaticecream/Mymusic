
#include"pch.h"
#include "cmysliderctrl.h"

CMySliderCtrl::CMySliderCtrl()
{
	m_dlg_bk_color = COLORREF(DLG_BK_COLOR);
	m_channel_bk_color = COLORREF(SLIDER_BK_COLOR);
	m_channel_left_color = COLORREF(SLIDER_LEFT_COLOR);
	m_thumb_color = COLORREF(SLIDER_THUMB_COLOR);
	m_thumb_on_color = COLORREF(SLIDER_THUMB_ON_COLOR);
	m_thumb_selected_color = COLORREF(SLIDER_THUMB_SELECTED_COLOR);
	m_thumb_rate = (float)0.6;
	thumb_down = TRUE;
	thumb_selected = TRUE;
	init_gdi_objs();
}
CMySliderCtrl::~CMySliderCtrl()
{
	delete_gdi_objs();
}

void CMySliderCtrl::init_gdi_objs()
{
	pen_thumb_selected.CreatePen(PS_DASHDOTDOT, 2, m_thumb_selected_color);
	pen_thumb.CreatePen(PS_DASHDOTDOT, 2, m_thumb_color);
	pen_thumb_on.CreatePen(PS_DASHDOTDOT, 2, m_thumb_on_color);
	brush_thumb_selected.CreateSolidBrush(m_thumb_selected_color);
	brush_thumb.CreateSolidBrush(m_thumb_color);
	brush_thumb_on.CreateSolidBrush(m_thumb_on_color);
}

void CMySliderCtrl::delete_gdi_objs()
{
	DeleteObject(pen_thumb_selected);
	DeleteObject(pen_thumb);
	DeleteObject(pen_thumb_on);
	DeleteObject(brush_thumb_selected);
	DeleteObject(brush_thumb);
	DeleteObject(brush_thumb_on);
}

BEGIN_MESSAGE_MAP(CMySliderCtrl, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CMySliderCtrl::OnPaint()
{
	CSliderCtrl::OnPaint();
	CDC* pDc = GetDC();
	owner_draw(pDc);
	ReleaseDC(pDc);
}

void CMySliderCtrl::owner_draw(CDC* pDc)
{
	CRect clientRect;
	GetClientRect(clientRect);
	CRect channelRect;
	GetChannelRect(&channelRect);
	CRect thumbRect;
	GetThumbRect(thumbRect);

	pDc->SetBkMode(TRANSPARENT);
	pDc->FillSolidRect(clientRect, m_dlg_bk_color);
	pDc->FillSolidRect(channelRect, m_channel_bk_color);
	pDc->Draw3dRect(channelRect, m_channel_bk_color, m_channel_bk_color);

	CRect leftRect;
	leftRect.left = channelRect.left;
	leftRect.top = channelRect.top;
	leftRect.bottom = channelRect.bottom;
	leftRect.right = thumbRect.left;

	pDc->FillSolidRect(leftRect, m_channel_left_color);
	pDc->Draw3dRect(leftRect, m_channel_left_color, m_channel_left_color);

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
	get_ellipse_rect(thumbRect);
	pDc->Rectangle(thumbRect);
	pDc->SelectObject(oldpen);
	pDc->SelectObject(oldbrush);
}

void CMySliderCtrl::get_ellipse_rect(CRect& rect)
{
	CPoint center = rect.CenterPoint();
	int length = 0;
	rect.Width() < rect.Height() ? length = (int)(rect.Height() * m_thumb_rate) : length = (int)(rect.Width() * m_thumb_rate);
	rect.left = center.x - length / 2;
	rect.right = center.x + length / 2;
	rect.top = center.y - length / 2;
	rect.bottom = center.y + length / 2;
}


void CMySliderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
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

void CMySliderCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	thumb_down = FALSE;
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CMySliderCtrl::OnMouseMove(UINT nFlags, CPoint point)
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