#include "pch.h"
#include "framework.h"
#include "MFCmusic.h"
#include "MFCmusicDlg.h"
#include "afxdialogex.h"


#pragma comment (lib,"winmm.lib")
#include "music.h"
#include <direct.h>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern MUSIC* music;
extern string* musiclist;
extern int NUMBER_LIST;
extern int number_list;

bool TOP = false;


void comboadd(CComboBox& combo, string address)
{
	int i = 0;
	int n = getnumber(address);
	string* str = new string[n + 1];
	getlist(str, address);
	for (i = 0;i < n;i++)
	{
		combo.AddString(str[i].c_str());
	}
	delete[]str;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CMFCmusicDlg 对话框



CMFCmusicDlg::CMFCmusicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMUSIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	allmusic = NULL;
	//countdown = NULL;
}
CMFCmusicDlg::~CMFCmusicDlg()
{
	if (allmusic != NULL)
	{
		delete allmusic;
		allmusic = NULL;
	}
	/*if (countdown != NULL)
	{
		delete countdown;
		countdown = NULL;
	}*/

}
void CMFCmusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_BUTTON2, button2);
	DDX_Control(pDX, IDC_BUTTON3, button3);
	DDX_Control(pDX, IDC_BUTTON4, button4);
	DDX_Control(pDX, IDC_BUTTON5, button5);
	DDX_Control(pDX, IDC_BUTTON6, button6);
	DDX_Control(pDX, IDC_BUTTON7, button7);
	DDX_Control(pDX, IDC_BUTTON8, button8);
	DDX_Control(pDX, IDC_BUTTON9, button9);
	DDX_Control(pDX, IDC_SLIDER1, slider1);
	DDX_Control(pDX, IDC_SLIDER2, slider2);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_COMBO2, combo2);
	DDX_Control(pDX, IDC_BUTTON10, button10);
}

BEGIN_MESSAGE_MAP(CMFCmusicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCmusicDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCmusicDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCmusicDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCmusicDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCmusicDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCmusicDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCmusicDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCmusicDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCmusicDlg::OnBnClickedButton9)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_MESSAGE(MM_MCINOTIFY, &CMFCmusicDlg::OnMmMcinotify)
	ON_MESSAGE(MM_CHILD, &CMFCmusicDlg::OnMmChild)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCmusicDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCmusicDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCmusicDlg::OnBnClickedButton10)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCmusicDlg 消息处理程序

BOOL CMFCmusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_BUTTON1)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON2)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON3)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON4)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON5)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON6)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON7)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON8)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON9)->ModifyStyle(0, BS_OWNERDRAW, 0);
	GetDlgItem(IDC_BUTTON10)->ModifyStyle(0, BS_OWNERDRAW, 0);
	buttondraw(button1, IDB_BITMAP2, IDB_BITMAP2_1);
	buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
	buttondraw(button3, IDB_BITMAP3, IDB_BITMAP3_1);
	buttondraw(button4, IDB_MODE0, IDB_MODE0);
	buttondraw(button5, IDB_BITMAP10, IDB_BITMAP10_1);
	buttondraw(button6, IDB_BITMAP10, IDB_BITMAP10_1);
	buttondraw(button7, IDB_DELETE, IDB_DELETE_1);
	buttondraw(button8, IDB_DELETE, IDB_DELETE_1);
	buttondraw(button9, IDB_BITMAP8_1, IDB_BITMAP8_1);
	buttondraw(button10, IDB_BITMAP5, IDB_BITMAP5_1);
	if (findfile("musiclist.ini"))
	{
		if (getnumber("musiclist")==0)
		{
			creatlist("musiclist", "mylist");
			creatlist("mylist");
		}
	}
	else
	{
		creatlist("musiclist","mylist");
		creatlist("mylist");
	}

	NUMBER_LIST = getnumber("musiclist");
	musiclist = new string[NUMBER_LIST + 1];
	getlist(musiclist, "musiclist");
	music = changelist(music, musiclist[0]);

	comboadd(combo1, "musiclist");
	comboadd(combo2, musiclist[0]);
	combo1.SetCurSel(0);
	combo2.SetCurSel(0);


	

	slider1.SetRange(0, 511);
	slider1.SetTicFreq(1);
	slider1.SetPos(0);

	slider2.SetRange(0, 10);
	slider2.SetTicFreq(1);
	slider2.SetPos(3);

	
	if (_access("music", 0) == -1)	//如果文件夹不存在
	{
		_mkdir("music");
	}

	srand(time(0));

	SetTimer(1, 1000, NULL);

	CDialogEx::OnInitDialog();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCmusicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCmusicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CPaintDC   dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BACKGROUND);  //对话框的背景图片  

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCmusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCmusicDlg::buttondraw(CBitmapButton &button, UINT ID1, UINT ID2, UINT ID3, UINT ID4)
{
	button.LoadBitmaps(ID1, ID2, ID3, ID4);
	button.SizeToContent();
	Invalidate();
}
void CMFCmusicDlg::buttondraw(CBitmapButton &button, UINT ID1, UINT ID2)
{
	button.LoadBitmaps(ID1, ID2, ID1, ID1);
	button.SizeToContent();
	Invalidate();
}


void CMFCmusicDlg::OnBnClickedButton1()
{
	int n = MUSIC::getnumber(1);
	int i = MUSIC::getnumber();
	music[i].close();
	if (n)
	{
		music[i].close();
		i = MUSIC::setnumber((i + n - 1) % n);
		if (music[i].open() && music[i].play())
		{
			buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			music[i].setvolume(MUSIC::getvolume());
			combo2.SetCurSel(i);
		}
		else
		{
			create_countdown();
		}
	}
}

void CMFCmusicDlg::OnBnClickedButton2()//播放暂停
{
	if (MUSIC::getnumber(1))
	{
		int i = MUSIC::getnumber();
		switch (MUSIC::getstate())
		{
		
		case 0:
			if (music[i].open() && music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			}
			else
			{
				create_countdown();
			}
			break;
		case 1:
			if (music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			}
			else
			{
				create_countdown();
			}
			break;
		case 2:
			if (music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			}
			else
			{
				create_countdown();
			}
			break;
		case 3:
			if (music[i].pause())
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
			else
			{
				create_countdown();
			}
			break;
		case 4:
			if (music[i].resume())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			}
			else
			{
				create_countdown();
			}
			break;
		case 5:
			if (music[i].pause())
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
			else
			{
				create_countdown();
			}
			break;
			//Invalidate();
		}
	}
}

void CMFCmusicDlg::OnBnClickedButton3()
{
	int n = MUSIC::getnumber(1);
	int i = MUSIC::getnumber();
	music[i].close();
	if (n)
	{
		i = MUSIC::setnumber((i + 1) % n);
		if (music[i].open() && music[i].play())
		{
			buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			music[i].setvolume(MUSIC::getvolume());
			combo2.SetCurSel(i);
		}
		else
		{
			create_countdown();
		}
		
	}
}

void CMFCmusicDlg::OnBnClickedButton4()
{
	switch (MUSIC::getmode())
	{
	case 0:
		MUSIC::setmode(1);
		buttondraw(button4, IDB_MODE1, IDB_MODE1);
		break;
	case 1:
		MUSIC::setmode(2);
		buttondraw(button4, IDB_MODE2, IDB_MODE2);
		break;
	case 2:
		MUSIC::setmode(3);
		buttondraw(button4, IDB_MODE3, IDB_MODE3);
		break;
	case 3:
		MUSIC::setmode(4);
		buttondraw(button4, IDB_MODE4, IDB_MODE4);
		break;
	case 4:
		MUSIC::setmode(0);
		buttondraw(button4, IDB_MODE0, IDB_MODE0);
		break;
	}
}

void CMFCmusicDlg::OnBnClickedButton5()
{
	CString data;
	combo1.GetWindowTextA(data);
	int j = findlist(string(data), "musiclist");
	if (j == -1)
	{
		switch (MessageBox(TEXT("是否添加歌单？"), TEXT(""), MB_YESNO))
		{
		case IDYES:
			creatlist("musiclist", string(data));
			creatlist(string(data));


			NUMBER_LIST = getnumber("musiclist");

			delete[]musiclist;
			musiclist = new string[NUMBER_LIST + 1];
			getlist(musiclist, "musiclist");

			combo1.ResetContent();
			comboadd(combo1, "musiclist");
			combo1.SetCurSel(number_list);

			number_list = NUMBER_LIST - 1;

			break;
		case IDNO:
			break;
		}
	}
	else if (j >= 0 && j < NUMBER_LIST && j != number_list)
	{
		int i = MUSIC::getnumber();
		music[i].close();
		number_list = j;
		music = changelist(music, musiclist[number_list]);

		combo2.ResetContent();
		comboadd(combo2, musiclist[number_list]);
		combo2.SetCurSel(0);

		i = MUSIC::setnumber(0);
		if (MUSIC::setnumber(getnumber(musiclist[number_list]), 1))
		{
			if (music[i].open() && music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
				music[i].setvolume(MUSIC::getvolume());
			}
			else
			{
				create_countdown();
			}
			
		}
		else
		{
			buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
		}
	}
	
}

void CMFCmusicDlg::OnBnClickedButton6()
{
	CString data;
	combo2.GetWindowTextA(data);
	int j = findlist(string(data), musiclist[number_list]);
	int i = MUSIC::getnumber();
	int n = MUSIC::getnumber(1);
	if (j == -1)
	{	
		if (findfile("music\\" + string(data) + ".mp3"))
		{
			music[i].close();
			creatlist(musiclist[number_list], string(data));
			music = changelist(music, musiclist[number_list]);
			n = MUSIC::setnumber(getnumber(musiclist[number_list]), 1);
			i = MUSIC::setnumber(n - 1);

			combo2.ResetContent();
			comboadd(combo2, musiclist[number_list]);
			combo2.SetCurSel(i);

			if (n)
			{
				if (music[i].open() && music[i].play())
				{
					buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
					music[i].setvolume(MUSIC::getvolume());
				}
				else
				{
					create_countdown();
				}
			}
			else
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
		}
		else
		{
			MessageBox(TEXT("添加歌曲失败"), TEXT(""), MB_OK);
			combo2.SetCurSel(i);
		}
		
		
	}
	else if (j >= 0 && j < n && j != i)
	{
		music[i].close();
		i=MUSIC::setnumber(j);
		combo2.SetCurSel(i);

		if (n)
		{
			if (music[i].open() && music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
				music[i].setvolume(MUSIC::getvolume());
			}
			else
			{
				create_countdown();
			}
			
		}
		else
		{
			buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
		}
	}

}

void CMFCmusicDlg::OnBnClickedButton7()
{
	CString data;
	combo1.GetWindowTextA(data);
	int e = findlist(string(data), "musiclist");

	if (e > -1)
	{
		if (e == number_list)
		{
			music[MUSIC::getnumber()].close();
			buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);

			deletelist(string(data), e);
			NUMBER_LIST = getnumber("musiclist");
			number_list = number_list % NUMBER_LIST;
			delete[]musiclist;
			musiclist = new string[NUMBER_LIST+1];
			getlist(musiclist, "musiclist");
			music = changelist(music, musiclist[number_list]);
			combo1.ResetContent();
			comboadd(combo1, "musiclist");
			combo1.SetCurSel(number_list);

			combo2.ResetContent();
			comboadd(combo2, musiclist[number_list]);
			combo2.SetCurSel(0);

		}
		else if(e<NUMBER_LIST)
		{
			if (number_list > e)
			{
				number_list -= 1;
			}
			deletelist(string(data), e);
			NUMBER_LIST = getnumber("musiclist");
			delete[]musiclist;
			musiclist = new string[NUMBER_LIST+1];
			getlist(musiclist, "musiclist");
			combo1.ResetContent();
			comboadd(combo1, "musiclist");
			combo1.SetCurSel(number_list);
		}

	}

}

void CMFCmusicDlg::OnBnClickedButton8()
{
	int i = MUSIC::getnumber();
	int n = MUSIC::getnumber(1);
	CString data;
	combo2.GetWindowTextA(data);
	int e = findlist(string(data), musiclist[number_list]);
	if (e > -1)
	{
		if (e == i)
		{
			music[i].close();
			buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			i = MUSIC::setnumber(i % n);

			deletelist(musiclist[number_list], string(data), e);
			n = MUSIC::setnumber(getnumber(musiclist[number_list]),1);

			music = changelist(music, musiclist[number_list]);

			i = MUSIC::setnumber(i);
			combo2.ResetContent();
			comboadd(combo2, musiclist[number_list]);
			combo2.SetCurSel(i);

			if (n)
			{
				if (music[i].open() && music[i].play())
				{
					buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
					music[i].setvolume(MUSIC::getvolume());
				}
				else
				{
					create_countdown();
				}
				
			}
			else
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}

		}
		else if (i<n)
		{
			if (i > e)
			{
				i = MUSIC::setnumber(i - 1);
			}
			deletelist(musiclist[number_list], string(data), e);
			MUSIC::setnumber(getnumber(musiclist[number_list]), 1);
			music = changelist(music, musiclist[number_list]);
			combo2.ResetContent();
			comboadd(combo2, musiclist[number_list]);
			combo2.SetCurSel(i);
		}
		
	}
}

void CMFCmusicDlg::OnBnClickedButton9()
{
	if (!TOP)
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		TOP = true;
		buttondraw(button9, IDB_BITMAP8, IDB_BITMAP8);
	}
	else
	{
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		TOP = false;
		buttondraw(button9, IDB_BITMAP8_1, IDB_BITMAP8_1);
	}
}

void CMFCmusicDlg::OnCbnSelchangeCombo1()
{
	int i = MUSIC::getnumber();
	music[i].close();
	number_list = combo1.GetCurSel();
	music = changelist(music, musiclist[number_list]);
	
	combo2.ResetContent();
	comboadd(combo2, musiclist[number_list]);
	combo2.SetCurSel(0);

	i = MUSIC::setnumber(0);
	if (MUSIC::setnumber(getnumber(musiclist[number_list]), 1))
	{
		if (music[i].open() && music[i].play())
		{
			buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			music[i].setvolume(MUSIC::getvolume());
		}
		else
		{
			create_countdown();
		}
	}
	else
	{
		buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
	}
}

void CMFCmusicDlg::OnCbnSelchangeCombo2()
{
	int i = MUSIC::getnumber();
	music[i].close();
	i = MUSIC::setnumber(combo2.GetCurSel());
	if (music[i].open() && music[i].play())
	{
		buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
		music[i].setvolume(MUSIC::getvolume());
	}
	else
	{
		create_countdown();
	}
}

void CMFCmusicDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int i = MUSIC::getnumber();
	if (pScrollBar == GetDlgItem(IDC_SLIDER1))
	{	
		music[i].close();
		music[i].open();
		music[i].setposition(double(music[i].get("length")) * slider1.GetPos() / 511);
		if (music[i].play())
		{
			buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
			music[i].setvolume(MUSIC::getvolume());
		}
		else
		{
			create_countdown();
		}
		
	}
	if (pScrollBar == GetDlgItem(IDC_SLIDER2))
	{
		if (music[i].getstate() == 0)
		{
			music[i].open();
		}
		music[i].setvolume(100 * slider2.GetPos());
	}
}

void CMFCmusicDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	
}

void CMFCmusicDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		int i = music[MUSIC::getnumber()].showposition();
		if (i >= 0)
		{
			slider1.SetPos(i);
		}
		break;
	}
}

afx_msg LRESULT CMFCmusicDlg::OnMmMcinotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 1:
		int i = MUSIC::getnumber();
		int n = MUSIC::getnumber(1);
		switch (MUSIC::getmode())
		{
		case 0:
			music[i].close();
			i=MUSIC::setnumber((i + 1) % n);
			combo2.SetCurSel(i);
			if (music[i].open() && music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
				music[i].setvolume(MUSIC::getvolume());
			}
			else
			{
				create_countdown();
			}
			break;
		case 1:
			music[i].close();
			if (music[i].open() && music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
				music[i].setvolume(MUSIC::getvolume());
			}
			else
			{
				create_countdown();
			}
			break;
		case 2:
			music[i].close();
			if (i + 1 < n)
			{
				i=MUSIC::setnumber(i + 1);
				combo2.SetCurSel(i);
				if (music[i].open() && music[i].play())
				{
					buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
					music[i].setvolume(MUSIC::getvolume());
				}
				else
				{
					create_countdown();
				}	
			}
			else
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
			break;
		case 3:
			music[i].close();
			i=MUSIC::setnumber(rand() % n);
			combo2.SetCurSel(i);
			if (music[i].open() && music[i].play())
			{
				buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
				music[i].setvolume(MUSIC::getvolume());
			}
			else
			{
				create_countdown();
			}
			break;

		case 4:
			if (music[i].close())
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
		}
		break;
	}
	return 0;
}

afx_msg LRESULT CMFCmusicDlg::OnMmChild(WPARAM wParam, LPARAM lParam)
{
	
	CString data = "";
	int j;
	int i;
	int n;
	switch (lParam)
	{
	case 0:
		data= ((BSTR)wParam);
		j = findlist(string(data), musiclist[number_list]);
		i = MUSIC::getnumber();
		n = MUSIC::getnumber(1);
		if (j == -1)
		{
			if (findfile("music\\" + string(data) + ".mp3"))
			{
				music[i].close();
				creatlist(musiclist[number_list], string(data));
				music = changelist(music, musiclist[number_list]);
				n = MUSIC::setnumber(getnumber(musiclist[number_list]), 1);
				i = MUSIC::setnumber(n - 1);

				combo2.ResetContent();
				comboadd(combo2, musiclist[number_list]);
				combo2.SetCurSel(i);
			}
			else
			{
				MessageBox(TEXT("添加歌曲失败"), TEXT(""), MB_OK);
				combo2.SetCurSel(i);
			}
			if (n)
			{
				if (music[i].open() && music[i].play())
				{
					buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
					music[i].setvolume(MUSIC::getvolume());
				}
				else
				{
					create_countdown();
				}
			}
			else
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}

		}
		else if (j >= 0 && j < n && j != i)
		{
			music[i].close();
			i = MUSIC::setnumber(j);
			combo2.SetCurSel(i);

			if (n)
			{
				if (music[i].open() && music[i].play())
				{
					buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
					music[i].setvolume(MUSIC::getvolume());
				}
				else
				{
					create_countdown();
				}
			}
			else
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
		}
		break;
	case 1:
		data = ((BSTR)wParam);
		switch (MessageBox("是否删除", "", MB_OKCANCEL))
		{
		case IDOK:
			remove("music\\" + data + ".mp3");
			break;
		case IDCANCEL:
			break;
		}
		break;
	case 2:
		
		switch (wParam)
		{
		case 0:
			i = MUSIC::getnumber();
			n = MUSIC::getnumber(1);
			music[i].close();
			buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);

			deletelist(musiclist[number_list], string(data), i);
			i = MUSIC::setnumber(i % n);

			n = MUSIC::setnumber(getnumber(musiclist[number_list]), 1);

			music = changelist(music, musiclist[number_list]);

			i = MUSIC::setnumber(i);
			combo2.ResetContent();
			comboadd(combo2, musiclist[number_list]);
			combo2.SetCurSel(i);

			if (n)
			{
				if (music[i].open() && music[i].play())
				{
					buttondraw(button2, IDB_BITMAP4, IDB_BITMAP4_1);
					music[i].setvolume(MUSIC::getvolume());
				}
				else
				{
					create_countdown();
				}

			}
			else
			{
				buttondraw(button2, IDB_BITMAP1, IDB_BITMAP1_1);
			}
			break;
		case 1:
			music[MUSIC::getnumber()].jump();
			break;
		}
		EnableWindow(1);
		break;
	}
	return 0;
}

void CMFCmusicDlg::OnBnClickedButton10()
{
	if (allmusic == NULL)
	{
		allmusic = new ALLMUSIC();

		allmusic->Create(IDD_ALLMUSIC, this);
	}
	allmusic->ShowWindow(SW_SHOW);
}
void CMFCmusicDlg::create_countdown()
{
	countdown.DoModal();
	combo2.SetCurSel(MUSIC::getnumber());
}



HBRUSH CMFCmusicDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	//判断当前控件的类型
	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:	//若传入进来的控件是EDIT
	{
		//获取Edit父控件的ID
		UINT nParentID = pWnd->GetParent()->GetDlgCtrlID();
		CRect rc;
		pWnd->GetClientRect(&rc);
		switch(nParentID)
		{
		case IDC_COMBO1:
			pDC->SetTextColor(combo1.COLOR_TEXT[0]);
			pDC->FillSolidRect(rc, combo1.COLOR_BK[0]);
			break;
		case IDC_COMBO2:
			pDC->SetTextColor(combo2.COLOR_TEXT[0]);
			pDC->FillSolidRect(rc, combo2.COLOR_BK[0]);
			break;
		}
	}
	default:
		break;
	}
	return hbr;
}
