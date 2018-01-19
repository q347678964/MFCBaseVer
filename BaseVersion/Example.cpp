#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "Example.h"
#include "BaseVersionDlg.h"
#include "png.h"

/*************************************************************************************/
//���졢��������
Example::Example(){

}

Example::~Example(){

}
/*************************************************************************************/
//���������
void Example::Init(void)
{
	this->Printf((CString)"���Կ�ʼ\r\n");
	g_PrintfSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
}
void Example::Exit(void)
{
	this->Printf((CString)"���Խ���\r\n");
}

void Example::LogPrintf(CString Context){
	static int FirstInFlag = 1;

	WaitForSingleObject(g_PrintfSemaphore, INFINITE);

	char Data[1000];
	int Len = g_FormatHandle.CStringToChar(Context,Data);

	if(FirstInFlag){
		FirstInFlag = 0;
		CFile LogFile(_T("../Output/Log.txt"),CFile::modeCreate | CFile::modeReadWrite);
		LogFile.Write(Data,Len);
		LogFile.Close();
	}else{
		CFile LogFile(_T("../Output/Log.txt"),CFile::modeReadWrite);
		LogFile.SeekToEnd();
		LogFile.Write(Data,Len);
		LogFile.Close();
	}

	ReleaseSemaphore(g_PrintfSemaphore, 1, NULL);
}

/*	PrintfToFile - ��Log��ӡ���ļ�����
*	
*/
void Example::PrintfToFile(CString Context){
	CTime time = CTime::GetCurrentTime();   ///����CTime����
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + (CString)("[Example]") + Context;
    this->LogPrintf(Context);
}

void Example::Printf(CString Context){
	CTime time = CTime::GetCurrentTime();   ///����CTime����
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + (CString)("[Example]") + Context;
    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->Printf(Context);
}

void Example::ProcessCtrl(int Num){

    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->ProcessCtrl(Num);
}
/*************************************************************************************/
//�̲߳���
DWORD WINAPI ThreadProc(LPVOID pParam)
{
	Example *Ex = (Example *)pParam;
	Ex->PrintfToFile((CString)"�߳�����\r\n");
	Sleep(1000);
	Ex->PrintfToFile((CString)"�߳̽���\r\n");
	return 0;
}

void Example::ThreadTest(void){
	this->PrintfToFile((CString)"�̲߳��Կ�ʼ\r\n");
	AfxBeginThread((AFX_THREADPROC)ThreadProc,this,THREAD_PRIORITY_HIGHEST);
	this->PrintfToFile((CString)"�߳��Ѿ�����\r\n");
}
/*************************************************************************************/
//ʱ���������
void Example::TimerTest(void){

	this->PrintfToFile((CString)"ʱ����Կ�ʼ\r\n");

	clock_t TimeStart,TimeEnd;
	unsigned int TimeSpend;
	TimeStart = clock();
	Sleep(100);
	TimeEnd = clock();

	TimeSpend = TimeEnd - TimeStart;

	CString TempCString;
	TempCString.Format(_T("ʱ����:%u����\r\n"),TimeSpend);
	this->PrintfToFile(TempCString);

	CTime time = CTime::GetCurrentTime();   ///����CTime����
#if 0
	int m_nYear = time.GetYear();      ///��
	int m_nMonth = time.GetMonth();      ///��
	int m_nDay = time.GetDay();      ///��
	int m_nHour = time.GetHour();      ///Сʱ
	int m_nMinute = time.GetMinute();   ///����
	int m_nSecond = time.GetSecond();   ///��
#endif
	CString m_strTime = time.Format("%Y-%m-%d %H:%M:%S");
	m_strTime += (CString)("\r\n");
	this->PrintfToFile(m_strTime);
	this->PrintfToFile((CString)"ʱ��������\r\n");

}

/*************************************************************************************/
//�ļ���������
void Example::FileOperation(void){
	this->PrintfToFile((CString)"�ļ��������Կ�ʼ\r\n");

	const char data[] = {"This is a test program"};
	CFile mFile(_T("../Output/Test.txt"),CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(data,sizeof(data));
	mFile.Close();

	this->PrintfToFile((CString)"�ļ������������\r\n");

}

/*************************************************************************************/
//����������
DWORD WINAPI ProcessTestThread(LPVOID pParam)
{
	Example *Ex = (Example *)pParam;
	Ex->PrintfToFile((CString)"�������������Կ�ʼ\r\n");
	for(int i=0;i<100;i++){
		Sleep(100);
		Ex->ProcessCtrl(i);
	}
	Ex->PrintfToFile((CString)"�������������Խ���\r\n");
	return 0;
}

void Example::ProcessTest(void){
	AfxBeginThread((AFX_THREADPROC)ProcessTestThread,this,THREAD_PRIORITY_HIGHEST);
}
/*************************************************************************************/
//��ȡ����IP��ַ
void Example::GetHostAddress(CString &strIPAddr)
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);

	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// ��ñ���������.

	hostent* hn;
	hn = gethostbyname(HostName);//���ݱ����������õ�����ip

	strIPAddr=inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);//��ip�����ַ�����ʽ

	WSACleanup();	//����ǵ��ͷ�
}

void Example::NetTest(void){
	this->PrintfToFile((CString)"������ز��Կ�ʼ\r\n");
	CString IPCString;
	this->GetHostAddress(IPCString);
	IPCString = (CString)("����IP��ַ:")+ IPCString + (CString)("\r\n");
	this->PrintfToFile(IPCString);
	this->PrintfToFile((CString)"������ز��Խ���\r\n");
}
/*************************************************************************************/
//Windows CMD�����������
void Example::WinCMDTest(void){
	this->PrintfToFile((CString)"Windows CMD�������:ipconfig\r\n");
	WinExec("cmd.exe /C ipconfig&&pause", SW_SHOWNORMAL);
}

void Example::OpencvFillRectangle(IplImage* img,UINT32 Startx,UINT32 Starty,UINT32 Endx,UINT32 Endy){
	CvPoint pt2[4] = {cvPoint(Startx,Starty),cvPoint(Endx,Starty),cvPoint(Endx,Endy),cvPoint(Startx,Endy)};
	cvFillConvexPoly(img,pt2,4,CV_RGB(0,0,0)); 
}

void on_Mouse(int event, int x, int y, int flags, void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���
{ 
	CString TempCString;
	Example *Ex = (Example *)ustc;

	if (event == CV_EVENT_MOUSEMOVE)//�ƶ�
	{
		//TempCString.Format(_T("(%d,%d)\r\n"),x,y);
		//CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
		//MainDlg->PathEditCtrl(TempCString);
	}else if(event == CV_EVENT_LBUTTONDOWN){	//�󵥻�
		TempCString.Format(_T("(%d,%d)\r\n"),x,y);
		AfxMessageBox(TempCString);
	}
}

void Example::OpencvTest(void)
{
	//IplImage *img = cvLoadImage("../Input/OpencvTest.jpg");
	//cvNamedWindow("Opencv����",CV_WINDOW_AUTOSIZE);
	//cvShowImage("Opencv����",img);

	IplImage *img2 = cvCreateImage(cvSize(800,800),8,3);

	{	//д�ֲ���
		char temp[16];
		int x  = 13 , y = 14;
		CvPoint pt = cvPoint(20,20); 
		CvFont font;   
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);   
		sprintf(temp,"(%d,%d)",x,y);   
		cvPutText(img2,temp, pt, &font, CV_RGB(255,0,0));   
	}
	
	{	//��Բ����,5�Ǵ�С
		CvPoint pt = cvPoint(50,50); 
		cvCircle(img2, pt, 5,CV_RGB(255,0,0) ,CV_FILLED, CV_AA, 0 );   
	}

	{	//���߲���
		cvLine(img2,cvPoint(100,100),cvPoint(200,200),CV_RGB(0,255,255));
	}

	{	//�����β���
        cvRectangle(img2, cvPoint(50,50), cvPoint(100,100), CV_RGB(255,255,255));  
		//�������״
		#define PointNum 4
		CvPoint pt1[PointNum] = {cvPoint(200,200),cvPoint(300,210),cvPoint(230,260),cvPoint(210,300)};
		cvFillConvexPoly(img2,pt1,PointNum,CV_RGB(250,0,0)); 

		this->OpencvFillRectangle(img2,400,400,500,500);

	}

	cvNamedWindow("Opencv�Ի�ͼ",CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("Opencv�Ի�ͼ", on_Mouse, this);
	cvShowImage("Opencv�Ի�ͼ",img2);

}

//��Ҫ��CString �� UNICODE�ĸ�ʽ.
void Example::FormatTest(void){
	char TestChar[] = {"Hello\r\n"};
	CString TestCString = this->g_FormatHandle.CharToCString(TestChar);			//Char->CString

	CString TestCString2("How old are you?");
	char TestChar2[1000];
	int Len = this->g_FormatHandle.CStringToChar(TestCString2,TestChar2);		//CString -> Char, Len = 17.
	
	CString TestCString3("123456");
	int TestInt = this->g_FormatHandle.CStringToInt(TestCString3);				//CString->Int

	int TempNum = 112233;
	CString TestCString4 = this->g_FormatHandle.IntToCString(TempNum);			//Int->CString
}

void Example::ScanWindowTest(void){
	FormatChange FC;
	Png PngHdlr(IDC_STATIC);
//1.�Ȼ�����洰��
    CWnd* pDesktopWnd = CWnd::GetDesktopWindow();
//2.���һ���Ӵ���
    CWnd* pWnd = pDesktopWnd->GetWindow(GW_CHILD);
//3.ѭ��ȡ�������µ������Ӵ���
    while(pWnd != NULL)
    {
       
		WCHAR TempWchar[256];
		char ClassTempChar[512];
		char WinTempChar[512];
		CString TempCString;
		 //��ô�������
		memset(TempWchar,0,sizeof(TempWchar));
		memset(ClassTempChar,0,sizeof(ClassTempChar));
		::GetClassName(pWnd->GetSafeHwnd(),TempWchar,sizeof(TempWchar)/sizeof(WCHAR));
		TempCString.Format(_T("��:%ws"),TempWchar);
		this->PrintfToFile(TempCString);
		FC.WcharToChar(TempWchar,ClassTempChar);

        //��ô��ڱ���
		memset(TempWchar,0,sizeof(TempWchar));
		memset(WinTempChar,0,sizeof(WinTempChar));
        ::GetWindowText(pWnd->GetSafeHwnd(),TempWchar,sizeof(TempWchar)/sizeof(WCHAR));
		TempCString.Format(_T("����:%ws\r\n"),TempWchar);
		this->PrintfToFile(TempCString);
		FC.WcharToChar(TempWchar,WinTempChar);
#if 1
		if(strcmp(ClassTempChar,"Photo_Lightweight_Viewer") == 0  &&  strcmp(WinTempChar,"52839202_12.png - Windows Photo Viewer") == 0){
			pWnd = pWnd->GetWindow(GW_CHILD);
			while(pWnd!=NULL){
				memset(TempWchar,0,sizeof(TempWchar));
				memset(ClassTempChar,0,sizeof(ClassTempChar));
				::GetClassName(pWnd->GetSafeHwnd(),TempWchar,sizeof(TempWchar)/sizeof(WCHAR));
				FC.WcharToChar(TempWchar,ClassTempChar);
				if(strcmp(ClassTempChar,"Photos_PhotoCanvas") == 0){
					this->ShowCwnd(pWnd,WinTempChar);
				}
				pWnd = pWnd->GetWindow(GW_HWNDNEXT);
			}
			pWnd = pWnd->GetParent();
		}
#endif
        pWnd = pWnd->GetWindow(GW_HWNDNEXT);
    }
}

void Example::PNGTest(void)
{	
	Png PngHdlr(IDC_STATIC);
	PngHdlr.Open("../Input/test.png");
}

/*
Key 37 = Left
Key 38 = Up
Key 39 = Right
Key 40 = Down
*/
void Example::DlgMsgListen(int MessageID)
{
	CString TempCStirng;
	TempCStirng.Format(_T("DlgMsgID = %d\r\n"),MessageID);
	this->Printf(TempCStirng);

	if(MessageID == 38)	//ץȡ�ؼ�UI���� 
		this->ShowCwnd(this->IDToCWnd(IDC_STATIC),"Win");

}