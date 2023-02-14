#pragma once
#include <string>
#include <io.h>
using namespace std;

// ALLMUSIC 对话框

class ALLMUSIC : public CDialogEx
{
	DECLARE_DYNAMIC(ALLMUSIC)

public:
	ALLMUSIC(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ALLMUSIC();
	bool list1add(string path);
	virtual BOOL OnInitDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALLMUSIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox list1;
	CEdit edit1;
	CBitmapButton button1;
	CBitmapButton button2;
	CMenu menu;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton1();//添加
	afx_msg void OnBnClickedButton2();//删除
	afx_msg void OnDropFiles(HDROP hDropInfo);//拖拽文件
	afx_msg void OnMenu1();//刷新
	afx_msg void OnMenu2();//打开存储文件
};
