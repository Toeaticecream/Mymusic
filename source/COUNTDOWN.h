#pragma once


// COUNTDOWN 对话框

class COUNTDOWN : public CDialogEx
{
	DECLARE_DYNAMIC(COUNTDOWN)

public:
	COUNTDOWN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COUNTDOWN();
	virtual BOOL OnInitDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUNTDOWN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton button1;
	CBitmapButton button2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
