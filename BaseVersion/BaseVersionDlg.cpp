
// BaseVersionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BaseVersion.h"
#include "BaseVersionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CBaseVersionDlg �Ի���




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


// CBaseVersionDlg ��Ϣ�������

BOOL CBaseVersionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_hIcon, TRUE); // Set big icon  
	SetIcon(m_hIcon, FALSE); // Set small icon; 

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->Printf((CString)("��ʼ���������!\r\n"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CBaseVersionDlg::DlgPaintInit(void)
{
	CWnd *pWnd;  
	int WinDlgWidth = 0;
	int WinDlgHeight = 0;
    CImage mImage;  
    if(mImage.Load(_T("../MyResource/����1.jpg")) == S_OK)  {
        //�����ô��ڱ��ֺͱ���ͼһ�� 
		WinDlgWidth = mImage.GetWidth();
		WinDlgHeight = mImage.GetHeight();
		SetWindowPos(NULL,0,0,WinDlgWidth,WinDlgHeight,SWP_NOMOVE);

		GetDlgItem( IDC_EDIT_Debug )->SetWindowPos( NULL,10,10,WinDlgWidth/3,WinDlgHeight/3,SWP_NOZORDER);//���Դ���
		mImage.Draw(GetDC()->GetSafeHdc(),CRect(0,0,WinDlgWidth,WinDlgHeight));//����

	}

}
void CBaseVersionDlg::OnPaint()
{
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
		this->DlgPaintInit();
		CDialog::OnPaint();
	}
	//this->Printf((CString)("�������!\r\n"));
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBaseVersionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�������� 
BOOL CBaseVersionDlg::PreTranslateMessage(MSG* pMsg)  
{  
    // TODO:  �ڴ����ר�ô����/����û���  
    if (pMsg->message == WM_KEYDOWN)  
    {  
        switch (pMsg->wParam)  
        {  
        case'I':  
            //if (::GetKeyState(VK_CONTROL) < 0)//�����Shift+X�����  
                //�ĳ�VK_SHIFT  
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