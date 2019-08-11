// Logindlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BaseVersion.h"
#include "Logindlg.h"
#include "afxdialogex.h"
#include "Config.h"
#include "FormatChange.h"
#include "NetControl.h"
#include "MailClient.h"
// Logindlg 对话框

IMPLEMENT_DYNAMIC(Logindlg, CDialog)

Logindlg::Logindlg(CWnd* pParent /*=NULL*/)
	: CDialog(Logindlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	this->CurLoginUser = LOGIN_USER_IDLE;
}

Logindlg::~Logindlg()
{
}

void Logindlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Logindlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LOGINOK, &Logindlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_REG, &Logindlg::OnBnClickedButtonReg)
END_MESSAGE_MAP()

void Logindlg::MoveTo(CWnd **SrcWnd,CWnd **DestWnd,int DestID,LOGIN_DEST_TYPE DestType,LOGIN_MOVE_DIR MoveMethod){
	CRect RectTemp;

	switch(MoveMethod){
		case LOGIN_MOVE_RIGHT:
			switch(DestType){
				case LOGIN_DEST_EDIT:
					(*SrcWnd)->GetWindowRect(RectTemp);//获取目标在屏幕上的坐标，需要转换到窗体坐标
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.right+10,RectTemp.top,0,0,SWP_NOZORDER|SWP_NOSIZE);	//路径窗口，只改变坐标，不改变大小
					break;
				case LOGIN_DEST_BUTTON:
					(*SrcWnd)->GetWindowRect(RectTemp);//获取目标在屏幕上的坐标，需要转换到窗体坐标
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.right+10,RectTemp.top,0,0,SWP_NOZORDER|SWP_NOSIZE);	//路径打开按钮，只改变坐标，不改变大小
					((CButton *)GetDlgItem(DestID))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));			//按钮图片
					//等效于这三句AfxGetApp()->LoadIcon(IDI_ICON1) 加载icon
					//((CMFCButton *)GetDlgItem(IDC_BUTTON_OpenFile)) 获取按钮句柄
					//SetIcon 按钮操作函数
					break;
			}
			break;
		case LOGIN_MOVE_BOTTOM:
			switch(DestType){
				case LOGIN_DEST_EDIT:
					(*SrcWnd)->GetWindowRect(RectTemp);//获取目标在屏幕上的坐标，需要转换到窗体坐标
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.left,RectTemp.bottom+10,0,0,SWP_NOZORDER|SWP_NOSIZE);	//路径窗口，只改变坐标，不改变大小
					break;
				case LOGIN_DEST_BUTTON:
					(*SrcWnd)->GetWindowRect(RectTemp);//获取目标在屏幕上的坐标，需要转换到窗体坐标
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.left,RectTemp.bottom+10,0,0,SWP_NOZORDER|SWP_NOSIZE);	//路径窗口，只改变坐标，不改变大小
					((CButton *)GetDlgItem(DestID))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));			//按钮图片
					break;
			}
			break;
		default:
			break;
	}
}
// Logindlg 消息处理程序
void Logindlg::DlgPaintInit(void)
{
	CImage mImage;  
    if(mImage.Load(_T(CFG_CSTRING_LOGIN_BGP)) == S_OK)  {
		CWnd *pWnd[20];  
		CRect RectTemp;
        //这里让窗口保持和背景图一致 
		int WinDlgWidth = mImage.GetWidth();
		int WinDlgHeight = mImage.GetHeight();
		SetWindowPos(NULL,0,0,WinDlgWidth,WinDlgHeight,SWP_NOMOVE);

		pWnd[0] = GetDlgItem(IDC_STATIC_PW);
		pWnd[0]->SetWindowPos( NULL,50,50,0,0,SWP_NOZORDER|SWP_NOSIZE);	//路径窗口，只改变坐标，不改变大小

		this->MoveTo(&pWnd[0],&pWnd[1],IDC_EDIT_LOGIN,LOGIN_DEST_EDIT,LOGIN_MOVE_BOTTOM);
		this->MoveTo(&pWnd[1],&pWnd[2],IDC_BUTTON_LOGINOK,LOGIN_DEST_BUTTON,LOGIN_MOVE_RIGHT);
		this->MoveTo(&pWnd[1],&pWnd[3],IDC_BUTTON_REG,LOGIN_DEST_BUTTON,LOGIN_MOVE_BOTTOM);
		{	//背景绘制
			CBitmap	bmpBackground;		//声明一个位图句柄
			FormatChange FC;
			FC.CImage2CBitmap(mImage,bmpBackground);
			//bmpBackground.LoadBitmap(IDB_BITMAP1);   //加载图片到位图句柄	

			CRect   WinDlg;   
			GetClientRect(&WinDlg);			//获取窗体的大小

			CDC *BGPDCMem = new CDC;;		//申请内存图片CDC
			CPaintDC WinDlgDc(this);					//这段代码用于设置背景图，初始化DC绘制对象为窗体本身
			BGPDCMem->CreateCompatibleDC(&WinDlgDc);   //创建一个与显示器设备内容兼容的内存设备内容
			BGPDCMem->SetBkMode(TRANSPARENT);
			BGPDCMem->SelectObject(&bmpBackground); //用SelectObject将位图选入内存设备内容  
#if 0	//拉伸方式绘制
			BITMAP   bitmap;	//BITMAP结构用于存放位图信息
			bmpBackground.GetBitmap(&bitmap);	//从图片中获取图片的宽高到bitmap
			WinDlgDc.StretchBlt(0,0,WinDlg.Width(),WinDlg.Height(),&g_BGPDCMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); //将DC内的图片内容拉伸之后PO窗体上,Stretch:拉伸
#else
			WinDlgDc.BitBlt(0,0,WinDlg.Width(),WinDlg.Height(),BGPDCMem,0,0,SRCCOPY);	//将内存的图片po到窗体上
#endif
			delete BGPDCMem;
		}
	}

	this->LoadPassword();
}

void Logindlg::OnPaint()
{
	static int FirstIn = 1;
	if(FirstIn){
		FirstIn = 0;
		this->DlgPaintInit();
	}
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
		CDialog::OnPaint();
	}
}

HBRUSH Logindlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{ 
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
	 switch (pWnd->GetDlgCtrlID()){
		case IDC_EDIT_LOGIN:
			pDC->SetTextColor(EDIT_PRINT_TEXT_RGB); //设置字体颜色
			pDC->SetBkMode(TRANSPARENT);	//设置字体背景为透明，这样才能直接带看Edit的颜色
			return (HBRUSH)CreateSolidBrush(EDIT_PRINT_BG_RGB);// 设置背景色画刷
			break;
		case IDC_STATIC_PW:
			pDC->SetBkMode(TRANSPARENT);   
			return (HBRUSH)::GetStockObject(NULL_BRUSH); 
			break;
	 }

	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_EDIT)//如果当前控件属于文本
	{ 

	}else if(nCtlColor==CTLCOLOR_STATIC){	//STATIC PICTURE

	}
	else if (nCtlColor==CTLCOLOR_BTN) //如果当前控件属于按钮
	{ 

	} 
	// TODO: Return a different brush if the default is not desired
	return hbr; 
}

void Logindlg::LoadPassword(void)
{
	CFileStatus status;
	CFile cfile;

	if(CFile::GetStatus(_T(LOGIN_PASSWORD_SAVEPATH), status ) )
	{
		if(status.m_size > 0 && status.m_size <= 128) {
			char password[128];
			CFile mFile(_T(LOGIN_PASSWORD_SAVEPATH),CFile::modeRead);
			mFile.Read(password,sizeof(password));
			CString PWCString = this->CharToCString(password);
			CEdit *LoginEdit =  (CEdit *)GetDlgItem(IDC_EDIT_LOGIN);
			LoginEdit->SetWindowText(PWCString);
			mFile.Close();
		}
	}
}

void Logindlg::SavePassword(CString Pw)
{	
	char password[128];
	int pwnum = 0;
	CFile mFile(_T(LOGIN_PASSWORD_SAVEPATH),CFile::modeCreate | CFile::modeReadWrite);
	pwnum = this->CStringToChar(Pw, password);
	mFile.Write(password,pwnum);
	mFile.Close();
}


DWORD WINAPI pLoginNotifyThread(LPVOID pParam)
{
	Logindlg *LoginDlg = (Logindlg *)pParam;

	if(LoginDlg->CurLoginUser == LOGIN_USER_CUSTOMER) {
		LoginDlg->CustomerLoginNotify();
	} else if(LoginDlg->CurLoginUser == LOGIN_USER_ROOT) {
		LoginDlg->RootLoginNotify();
	}

	LoginDlg->CurLoginUser = LOGIN_USER_IDLE;

	return 0;
}

void Logindlg::LoginNotifyThreadStart(LOGIN_USER LoginUser){
	if(this->CurLoginUser == LOGIN_USER_IDLE) {
		this->CurLoginUser = LoginUser;
		AfxBeginThread((AFX_THREADPROC)pLoginNotifyThread,this,THREAD_PRIORITY_HIGHEST);
	}
}

void Logindlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LoginCstring;
	net_control NetCHdlr;

	CEdit *LoginEdit =  (CEdit *)GetDlgItem(IDC_EDIT_LOGIN);

	LoginEdit->GetWindowText(LoginCstring);

	if(NetCHdlr.CreatePawword() == LoginCstring) {
		this->SavePassword(LoginCstring);
		this->LoginNotifyThreadStart(LOGIN_USER_CUSTOMER);
		CDialog::OnOK();
	} else if(LOGIN_PASSWORD_ROOT == LoginCstring) {
		this->LoginNotifyThreadStart(LOGIN_USER_ROOT);
		CDialog::OnOK();
	}else {
		AfxMessageBox(CString("登录密码错误！"));
	}
}

void Logindlg::RootLoginNotify(void)
{
	mail_client MailHdlr;
	net_control NetCHdlr;

	CString NetIp;
	CString LocalIp;
	CString PCName;
	CString MailContext;
	CString MAC;
	CString SoftwareName = CString(SOFTWARE_NAME);

	NetIp = NetCHdlr.get_netip();				//获取IP地址信息
	NetIp = CString("[外网IP:") + NetIp + CString("]\n");
	LocalIp = NetCHdlr.get_localip();
	LocalIp = CString("[局域网IP:") + LocalIp + CString("]\n");
	MAC = NetCHdlr.get_mac();
	MAC = CString("[网卡地址:") + MAC + CString("]\n");
	PCName = NetCHdlr.get_pcname();
	PCName = CString("[主机名:") + PCName + CString("]\n");

	MailHdlr.SetMailSubject(CString("Use Report with root"));
	MailContext = NetIp + LocalIp + MAC + PCName + CString("I'm using ") + SoftwareName;

	MailHdlr.SetMailContext(MailContext);
	
	MailHdlr.Send();
}

void Logindlg::CustomerLoginNotify(void)
{
	mail_client MailHdlr;
	net_control NetCHdlr;

	CString NetIp;
	CString LocalIp;
	CString PCName;
	CString MailContext;
	CString MAC;
	CString SoftwareName = CString(SOFTWARE_NAME);

	NetIp = NetCHdlr.get_netip();				//获取IP地址信息
	NetIp = CString("[外网IP:") + NetIp + CString("]\n");
	LocalIp = NetCHdlr.get_localip();
	LocalIp = CString("[局域网IP:") + LocalIp + CString("]\n");
	MAC = NetCHdlr.get_mac();
	MAC = CString("[网卡地址:") + MAC + CString("]\n");
	PCName = NetCHdlr.get_pcname();
	PCName = CString("[主机名:") + PCName + CString("]\n");

	MailHdlr.SetMailSubject(CString("Use Report with password"));
	MailContext = NetIp + LocalIp + MAC + PCName + CString("I'm using ") + SoftwareName;

	MailHdlr.SetMailContext(MailContext);
	
	MailHdlr.Send();
}

void Logindlg::OnBnClickedButtonReg()
{
	mail_client MailHdlr;
	net_control NetCHdlr;

	CString NetIp;
	CString LocalIp;
	CString PCName;
	CString MailContext;
	CString MAC;
	CString Password;
	CString SoftwareName = CString(SOFTWARE_NAME);

	NetIp = NetCHdlr.get_netip();				//获取IP地址信息
	NetIp = CString("[外网IP:") + NetIp + CString("]\n");
	LocalIp = NetCHdlr.get_localip();
	LocalIp = CString("[局域网IP:") + LocalIp + CString("]\n");
	MAC = NetCHdlr.get_mac();
	MAC = CString("[网卡地址:") + MAC + CString("]\n");
	PCName = NetCHdlr.get_pcname();
	PCName = CString("[主机名:") + PCName + CString("]\n");
	Password = NetCHdlr.CreatePawword();
	Password = CString("[秘钥:") + Password + CString("]\n");


	MailHdlr.SetMailSubject(CString("Register Report"));

	MailContext = NetIp + LocalIp + MAC + PCName + Password + CString("	I want to use ") + SoftwareName;

	MailHdlr.SetMailContext(MailContext);
	
	MailHdlr.Send();

	AfxMessageBox(CString("注册完成，请与开发者联系.\n qq/wechat:347678964"));
}
