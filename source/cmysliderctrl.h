#ifndef CMYSLIDERCTRL_H
#define CMYSLIDERCTRL_H

//#include "afxcmn.h"
#define SLIDER_BK_COLOR RGB(0,0,255)	
#define SLIDER_LEFT_COLOR RGB(246, 179, 127)
#define SLIDER_THUMB_COLOR RGB(255,105,105)
#define SLIDER_THUMB_ON_COLOR RGB(0,255,0)
#define SLIDER_THUMB_SELECTED_COLOR  RGB(210,105,30)
#define DLG_BK_COLOR RGB(240, 255, 255)
class CMySliderCtrl :public CSliderCtrl
{
public:
	CMySliderCtrl();
	virtual   ~CMySliderCtrl();
	afx_msg   void OnPaint();
	afx_msg   void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg   void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg	  void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void	  set_bk_color(COLORREF bk) { m_dlg_bk_color = bk; }
	void	  set_thumb_rate(float rate) { m_thumb_rate = rate; }
	void	  set_thumb_colors(COLORREF out, COLORREF in, COLORREF highlight) { m_thumb_color = out; m_thumb_on_color = in; m_thumb_color = highlight; init_gdi_objs(); }
	void	  set_channel_colors(COLORREF bk, COLORREF left) { m_channel_bk_color = bk; m_channel_left_color = left;  init_gdi_objs(); }
private:
	void	  init_gdi_objs();
	void	  delete_gdi_objs();
	void	  owner_draw(CDC* pDc);
	void	  get_ellipse_rect(CRect& rect);
private:
	COLORREF  m_dlg_bk_color;
	COLORREF  m_channel_bk_color;
	COLORREF  m_channel_left_color;
	COLORREF  m_thumb_color;
	COLORREF  m_thumb_on_color;
	COLORREF  m_thumb_selected_color;
	float	  m_thumb_rate;
	BOOL	  thumb_down;
	BOOL	  thumb_selected;
	CPen	  pen_thumb_selected;
	CPen	  pen_thumb;
	CPen	  pen_thumb_on;
	CBrush	  brush_thumb_selected;
	CBrush	  brush_thumb;
	CBrush	  brush_thumb_on;

};

#endif