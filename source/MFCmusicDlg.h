
// MFCmusicDlg.h: 头文件
//


// CMFCmusicDlg 对话框
class CMFCmusicDlg : public CDialogEx
{
// 构造
public:
	CMFCmusicDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMFCmusicDlg();
	ALLMUSIC* allmusic;
	COUNTDOWN countdown;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMUSIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LRESULT OnMmMcinotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMmChild(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton button1;
	CBitmapButton button2;
	CBitmapButton button3;
	CBitmapButton button4;
	CBitmapButton button5;
	CBitmapButton button6;
	CBitmapButton button7;
	CBitmapButton button8;
	CBitmapButton button9;
	void buttondraw(CBitmapButton& button, UINT ID1, UINT ID2, UINT ID3, UINT ID4);
	void buttondraw(CBitmapButton& button, UINT ID1, UINT ID2);
	afx_msg void OnBnClickedButton1();//上一曲
	afx_msg void OnBnClickedButton2();//播放/暂停
	afx_msg void OnBnClickedButton3();//下一曲
	afx_msg void OnBnClickedButton4();//播放模式
	afx_msg void OnBnClickedButton5();//添加歌单
	afx_msg void OnBnClickedButton6();//添加歌曲
	afx_msg void OnBnClickedButton7();//删除歌单
	afx_msg void OnBnClickedButton8();//删除歌曲
	afx_msg void OnBnClickedButton9();//置顶
	CCustomSlider slider1;
	CCustomSlider slider2;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//音量和进度
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CCustomComboBox combo1;
	CCustomComboBox combo2;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	CBitmapButton button10;
	afx_msg void OnBnClickedButton10();//查找音乐
	void create_countdown();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


