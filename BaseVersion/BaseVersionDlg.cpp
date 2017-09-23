
// BaseVersionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BaseVersion.h"
#include "BaseVersionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBaseVersionDlg 对话框




CBaseVersionDlg::CBaseVersionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseVersionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CBaseVersionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseVersionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CBaseVersionDlg 消息处理程序

BOOL CBaseVersionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_hIcon, TRUE); // Set big icon  
	SetIcon(m_hIcon, FALSE); // Set small icon; 

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->Printf((CString)("初始化窗体完成!\r\n"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBaseVersionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CBaseVersionDlg::DlgPaintInit(void)
{
	CWnd *pWnd;  
	int WinDlgWidth = 0;
	int WinDlgHeight = 0;
    CImage mImage;  
    if(mImage.Load(_T("../MyResource/背景1.jpg")) == S_OK)  {
        //这里让窗口保持和背景图一致 
		WinDlgWidth = mImage.GetWidth();
		WinDlgHeight = mImage.GetHeight();
		SetWindowPos(NULL,0,0,WinDlgWidth,WinDlgHeight,SWP_NOMOVE);

		GetDlgItem( IDC_EDIT_Debug )->SetWindowPos( NULL,10,10,WinDlgWidth/3,WinDlgHeight/3,SWP_NOZORDER);//调试窗口
		mImage.Draw(GetDC()->GetSafeHdc(),CRect(0,0,WinDlgWidth,WinDlgHeight));//背景

	}

}
void CBaseVersionDlg::OnPaint()
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
		this->DlgPaintInit();
		CDialog::OnPaint();
	}
	//this->Printf((CString)("绘制完成!\r\n"));
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBaseVersionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//按键监听 
BOOL CBaseVersionDlg::PreTranslateMessage(MSG* pMsg)  
{  
    // TODO:  在此添加专用代码和/或调用基类  
    if (pMsg->message == WM_KEYDOWN)  
    {  
        switch (pMsg->wParam)  
        {  
        case'I':  
            //if (::GetKeyState(VK_CONTROL) < 0)//如果是Shift+X这里就  
                //改成VK_SHIFT  
                MessageBox(_T("hello"));  
            return TRUE;  
        }  
    }  
    return CDialog::PreTranslateMessage(pMsg);  
}  

BOOL CBaseVersionDlg::Printf(CString string){
	static CString DebugCStringAll;
	string = (CString)"[Dlg]" + string;
	DebugCStringAll += string;
	SetDlgItemText(IDC_EDIT_Debug,DebugCStringAll);
	return 0;
}