// Logindlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BaseVersion.h"
#include "Logindlg.h"
#include "afxdialogex.h"
#include "Config.h"
#include "FormatChange.h"
#include "NetControl.h"
#include "MailClient.h"
// Logindlg �Ի���

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
					(*SrcWnd)->GetWindowRect(RectTemp);//��ȡĿ������Ļ�ϵ����꣬��Ҫת������������
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.right+10,RectTemp.top,0,0,SWP_NOZORDER|SWP_NOSIZE);	//·�����ڣ�ֻ�ı����꣬���ı��С
					break;
				case LOGIN_DEST_BUTTON:
					(*SrcWnd)->GetWindowRect(RectTemp);//��ȡĿ������Ļ�ϵ����꣬��Ҫת������������
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.right+10,RectTemp.top,0,0,SWP_NOZORDER|SWP_NOSIZE);	//·���򿪰�ť��ֻ�ı����꣬���ı��С
					((CButton *)GetDlgItem(DestID))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));			//��ťͼƬ
					//��Ч��������AfxGetApp()->LoadIcon(IDI_ICON1) ����icon
					//((CMFCButton *)GetDlgItem(IDC_BUTTON_OpenFile)) ��ȡ��ť���
					//SetIcon ��ť��������
					break;
			}
			break;
		case LOGIN_MOVE_BOTTOM:
			switch(DestType){
				case LOGIN_DEST_EDIT:
					(*SrcWnd)->GetWindowRect(RectTemp);//��ȡĿ������Ļ�ϵ����꣬��Ҫת������������
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.left,RectTemp.bottom+10,0,0,SWP_NOZORDER|SWP_NOSIZE);	//·�����ڣ�ֻ�ı����꣬���ı��С
					break;
				case LOGIN_DEST_BUTTON:
					(*SrcWnd)->GetWindowRect(RectTemp);//��ȡĿ������Ļ�ϵ����꣬��Ҫת������������
					ScreenToClient(RectTemp);
					(*DestWnd) = GetDlgItem(DestID);
					(*DestWnd)->SetWindowPos( NULL,RectTemp.left,RectTemp.bottom+10,0,0,SWP_NOZORDER|SWP_NOSIZE);	//·�����ڣ�ֻ�ı����꣬���ı��С
					((CButton *)GetDlgItem(DestID))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));			//��ťͼƬ
					break;
			}
			break;
		default:
			break;
	}
}
// Logindlg ��Ϣ�������
void Logindlg::DlgPaintInit(void)
{
	CImage mImage;  
    if(mImage.Load(_T(CFG_CSTRING_LOGIN_BGP)) == S_OK)  {
		CWnd *pWnd[20];  
		CRect RectTemp;
        //�����ô��ڱ��ֺͱ���ͼһ�� 
		int WinDlgWidth = mImage.GetWidth();
		int WinDlgHeight = mImage.GetHeight();
		SetWindowPos(NULL,0,0,WinDlgWidth,WinDlgHeight,SWP_NOMOVE);

		pWnd[0] = GetDlgItem(IDC_STATIC_PW);
		pWnd[0]->SetWindowPos( NULL,50,50,0,0,SWP_NOZORDER|SWP_NOSIZE);	//·�����ڣ�ֻ�ı����꣬���ı��С

		this->MoveTo(&pWnd[0],&pWnd[1],IDC_EDIT_LOGIN,LOGIN_DEST_EDIT,LOGIN_MOVE_BOTTOM);
		this->MoveTo(&pWnd[1],&pWnd[2],IDC_BUTTON_LOGINOK,LOGIN_DEST_BUTTON,LOGIN_MOVE_RIGHT);
		this->MoveTo(&pWnd[1],&pWnd[3],IDC_BUTTON_REG,LOGIN_DEST_BUTTON,LOGIN_MOVE_BOTTOM);
		{	//��������
			CBitmap	bmpBackground;		//����һ��λͼ���
			FormatChange FC;
			FC.CImage2CBitmap(mImage,bmpBackground);
			//bmpBackground.LoadBitmap(IDB_BITMAP1);   //����ͼƬ��λͼ���	

			CRect   WinDlg;   
			GetClientRect(&WinDlg);			//��ȡ����Ĵ�С

			CDC *BGPDCMem = new CDC;;		//�����ڴ�ͼƬCDC
			CPaintDC WinDlgDc(this);					//��δ����������ñ���ͼ����ʼ��DC���ƶ���Ϊ���屾��
			BGPDCMem->CreateCompatibleDC(&WinDlgDc);   //����һ������ʾ���豸���ݼ��ݵ��ڴ��豸����
			BGPDCMem->SetBkMode(TRANSPARENT);
			BGPDCMem->SelectObject(&bmpBackground); //��SelectObject��λͼѡ���ڴ��豸����  
#if 0	//���췽ʽ����
			BITMAP   bitmap;	//BITMAP�ṹ���ڴ��λͼ��Ϣ
			bmpBackground.GetBitmap(&bitmap);	//��ͼƬ�л�ȡͼƬ�Ŀ�ߵ�bitmap
			WinDlgDc.StretchBlt(0,0,WinDlg.Width(),WinDlg.Height(),&g_BGPDCMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); //��DC�ڵ�ͼƬ��������֮��PO������,Stretch:����
#else
			WinDlgDc.BitBlt(0,0,WinDlg.Width(),WinDlg.Height(),BGPDCMem,0,0,SRCCOPY);	//���ڴ��ͼƬpo��������
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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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
			pDC->SetTextColor(EDIT_PRINT_TEXT_RGB); //����������ɫ
			pDC->SetBkMode(TRANSPARENT);	//�������屳��Ϊ͸������������ֱ�Ӵ���Edit����ɫ
			return (HBRUSH)CreateSolidBrush(EDIT_PRINT_BG_RGB);// ���ñ���ɫ��ˢ
			break;
		case IDC_STATIC_PW:
			pDC->SetBkMode(TRANSPARENT);   
			return (HBRUSH)::GetStockObject(NULL_BRUSH); 
			break;
	 }

	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_EDIT)//�����ǰ�ؼ������ı�
	{ 

	}else if(nCtlColor==CTLCOLOR_STATIC){	//STATIC PICTURE

	}
	else if (nCtlColor==CTLCOLOR_BTN) //�����ǰ�ؼ����ڰ�ť
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(CString("��¼�������"));
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

	NetIp = NetCHdlr.get_netip();				//��ȡIP��ַ��Ϣ
	NetIp = CString("[����IP:") + NetIp + CString("]\n");
	LocalIp = NetCHdlr.get_localip();
	LocalIp = CString("[������IP:") + LocalIp + CString("]\n");
	MAC = NetCHdlr.get_mac();
	MAC = CString("[������ַ:") + MAC + CString("]\n");
	PCName = NetCHdlr.get_pcname();
	PCName = CString("[������:") + PCName + CString("]\n");

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

	NetIp = NetCHdlr.get_netip();				//��ȡIP��ַ��Ϣ
	NetIp = CString("[����IP:") + NetIp + CString("]\n");
	LocalIp = NetCHdlr.get_localip();
	LocalIp = CString("[������IP:") + LocalIp + CString("]\n");
	MAC = NetCHdlr.get_mac();
	MAC = CString("[������ַ:") + MAC + CString("]\n");
	PCName = NetCHdlr.get_pcname();
	PCName = CString("[������:") + PCName + CString("]\n");

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

	NetIp = NetCHdlr.get_netip();				//��ȡIP��ַ��Ϣ
	NetIp = CString("[����IP:") + NetIp + CString("]\n");
	LocalIp = NetCHdlr.get_localip();
	LocalIp = CString("[������IP:") + LocalIp + CString("]\n");
	MAC = NetCHdlr.get_mac();
	MAC = CString("[������ַ:") + MAC + CString("]\n");
	PCName = NetCHdlr.get_pcname();
	PCName = CString("[������:") + PCName + CString("]\n");
	Password = NetCHdlr.CreatePawword();
	Password = CString("[��Կ:") + Password + CString("]\n");


	MailHdlr.SetMailSubject(CString("Register Report"));

	MailContext = NetIp + LocalIp + MAC + PCName + Password + CString("	I want to use ") + SoftwareName;

	MailHdlr.SetMailContext(MailContext);
	
	MailHdlr.Send();

	AfxMessageBox(CString("ע����ɣ����뿪������ϵ.\n qq/wechat:347678964"));
}
