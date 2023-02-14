// ALLMUSIC.cpp: 实现文件
//

#include "pch.h"

#include "ALLMUSIC.h"
#include "afxdialogex.h"

bool ALLMUSIC::list1add(string path)
{
	_finddata_t file;
	intptr_t HANDLE;
	HANDLE = _findfirst(path.c_str(), &file);
	string str;
	if (HANDLE == -1L)
	{
		return false;
	}
	do
	{
		str = file.name;
		str.erase(str.end() - 4, str.end());
		list1.AddString((str.c_str()));
	} while (_findnext(HANDLE, &file) == 0);
	_findclose(HANDLE);
	return true;
}

// ALLMUSIC 对话框

IMPLEMENT_DYNAMIC(ALLMUSIC, CDialogEx)

ALLMUSIC::ALLMUSIC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALLMUSIC, pParent)
{

}

ALLMUSIC::~ALLMUSIC()
{
	
}

void ALLMUSIC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list1);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_BUTTON2, button2);
}

BOOL ALLMUSIC::OnInitDialog()
{
	
	GetDlgItem(IDC_BUTTON1)->ModifyStyle(0, BS_OWNERDRAW, 0);
	button1.LoadBitmaps(IDB_BITMAP10, IDB_BITMAP10_1, IDB_BITMAP10, IDB_BITMAP10);
	button1.SizeToContent();

	GetDlgItem(IDC_BUTTON2)->ModifyStyle(0, BS_OWNERDRAW, 0);
	button2.LoadBitmaps(IDB_DELETE, IDB_DELETE_1, IDB_DELETE, IDB_DELETE);
	button2.SizeToContent();
	Invalidate();
	
	menu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号
	SetMenu(&menu);

	CDialogEx::OnInitDialog();
	list1add("music\\*.mp3");
	return true;
}

BEGIN_MESSAGE_MAP(ALLMUSIC, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &ALLMUSIC::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &ALLMUSIC::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ALLMUSIC::OnBnClickedButton2)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MENU_32771, &ALLMUSIC::OnMenu1)
	ON_COMMAND(ID_MENU_32772, &ALLMUSIC::OnMenu2)
END_MESSAGE_MAP()

void ALLMUSIC::OnLbnSelchangeList1()
{
	// TODO: 鍦ㄦ娣诲姞鎺т欢閫氱煡澶勭悊绋嬪簭浠ｇ爜
	CString str;
	list1.GetText(list1.GetCurSel(), str);
	edit1.SetWindowTextA(str);
}
// ALLMUSIC 消息处理程序


void ALLMUSIC::OnBnClickedButton1()
{
	CString str;
	edit1.GetWindowTextA(str);
	string s = str;
	GetParent()->SendMessage(MM_CHILD, (WPARAM)str.AllocSysString(),0);
}


void ALLMUSIC::OnBnClickedButton2()
{
	CString str;
	edit1.GetWindowTextA(str);
	string s = str;
	GetParent()->SendMessage(MM_CHILD, (WPARAM)str.AllocSysString(), 1);
	list1.ResetContent();
	list1add("music\\*.mp3");
}


void ALLMUSIC::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和
	

	int file_number = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	TCHAR file_name[MAX_PATH] = {};
	string name;
	string ending;

	switch (MessageBox("是否添加到文件夹", "Addmusic", MB_YESNO))
	{
	case IDYES:
		file_number--;
		for (file_number;file_number>=0;file_number--)
		{
			DragQueryFile(hDropInfo, file_number, file_name, MAX_PATH);
			name = file_name;
			ending= name.substr(name.find_last_of('.') + 1);
			if (ending == "mp3")
			{
				name = name.substr(name.find_last_of('\\') + 1);
				name = "music\\" + name;
				CopyFile(file_name, name.c_str(), FALSE);
			}
		}

		break;
	case IDNO:
		break;
	}
	
	list1.ResetContent();
	list1add("music\\*.mp3");
	
	CDialogEx::OnDropFiles(hDropInfo);
}


void ALLMUSIC::OnMenu1()
{
	list1.ResetContent();
	list1add("music\\*.mp3");
}


void ALLMUSIC::OnMenu2()
{
	ShellExecute(NULL, "open", NULL, NULL, "music", SW_SHOWNORMAL);
}
