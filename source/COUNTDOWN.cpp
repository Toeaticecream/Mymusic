// COUNTDOWN.cpp: 实现文件
//

#include "pch.h"
#include "COUNTDOWN.h"
#include "afxdialogex.h"

char Time = '5';
// COUNTDOWN 对话框

IMPLEMENT_DYNAMIC(COUNTDOWN, CDialogEx)

COUNTDOWN::COUNTDOWN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COUNTDOWN, pParent)
{

}

COUNTDOWN::~COUNTDOWN()
{
}

void COUNTDOWN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_BUTTON2, button2);
}

BOOL COUNTDOWN::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(0, 1000, NULL);
	Time = '5';
	return true;
}

BEGIN_MESSAGE_MAP(COUNTDOWN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &COUNTDOWN::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &COUNTDOWN::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// COUNTDOWN 消息处理程序
void COUNTDOWN::OnBnClickedButton1()//删除 delete
{
	GetParent()->SendMessage(MM_CHILD, 0, 2);
	KillTimer(0);
	EndDialog(0);
}
void COUNTDOWN::OnBnClickedButton2()//跳过 skip
{
	GetParent()->SendMessage(MM_CHILD, 1, 2);
	KillTimer(0);
	EndDialog(0);
}

void COUNTDOWN::OnClose()//关闭 close
{
	GetParent()->SendMessage(MM_CHILD, 1, 2);
	KillTimer(0);
	EndDialog(0);
	CDialogEx::OnClose();
}


void COUNTDOWN::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 0://倒计时5s Countdown
		if (Time>'0')
		{
			Time--;
		}
		else
		{
			GetParent()->SendMessage(MM_CHILD, 1, 2);
			KillTimer(0);
			EndDialog(0);
		}
		CString str = "";
		str = Time;
		str = "跳过(" + str + "s)";
		button2.SetWindowText(str);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
