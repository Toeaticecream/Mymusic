#pragma once
#include <afxcmn.h>
class CCustomSlider :public CSliderCtrl
{
public:
	CCustomSlider();
	virtual   ~CCustomSlider() { delete_gdi_objs(); }
	afx_msg   void OnPaint();
	afx_msg   void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg   void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg	  void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void	  set_bk_color(COLORREF bk) { COLOR_BK = bk; }
	void	  set_thumb_rate(float rate) { m_thumb_rate = rate; }
	void	  set_thumb_colors(COLORREF out, COLORREF in, COLORREF highlight) { COLOR_BUTTON_UP = out; COLOR_BUTTON_ON = in; COLOR_BUTTON_UP = highlight; init_gdi_objs(); }
	void	  set_channel_colors(COLORREF bk, COLORREF left) { COLOR_RIGHT = bk; COLOR_LEFT = left;  init_gdi_objs(); }
private:
	void	  init_gdi_objs();
	void	  delete_gdi_objs();
	void	  owner_draw(CDC* pDc);
	void	  get_ellipse_rect(CRect& rect);
private:
	COLORREF  COLOR_BK;
	COLORREF  COLOR_RIGHT;
	COLORREF  COLOR_LEFT;
	COLORREF  COLOR_BUTTON_UP;
	COLORREF  COLOR_BUTTON_ON;
	COLORREF  COLOR_BUTTON_DOWN;
	INT	  m_thumb_rate;
	BOOL	  thumb_down;
	BOOL	  thumb_selected;
	CPen	  pen_thumb_selected;
	CPen	  pen_thumb;
	CPen	  pen_thumb_on;
	CBrush	  brush_thumb_selected;
	CBrush	  brush_thumb;
	CBrush	  brush_thumb_on;
};

