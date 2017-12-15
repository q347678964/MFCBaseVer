#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "Example.h"
#include "BaseVersionDlg.h"


/*************************************************************************************/
//���졢��������
Example::Example(){
	this->Printf((CString)"***********************\r\n");
}

Example::~Example(){

}
/*************************************************************************************/
//���������
void Example::Printf(CString Context){
	CTime time = CTime::GetCurrentTime();   ///����CTime����
	CString m_strTime = time.Format("[%H:%M:%S]");

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
	Ex->Printf((CString)"�߳�����\r\n");
	Sleep(1000);
	Ex->Printf((CString)"�߳̽���\r\n");
	return 0;
}

void Example::ThreadTest(void){
	this->Printf((CString)"�̲߳��Կ�ʼ\r\n");
	AfxBeginThread((AFX_THREADPROC)ThreadProc,this,THREAD_PRIORITY_HIGHEST);
	this->Printf((CString)"�߳��Ѿ�����\r\n");
}
/*************************************************************************************/
//ʱ���������
void Example::TimerTest(void){

	this->Printf((CString)"ʱ����Կ�ʼ\r\n");

	clock_t TimeStart,TimeEnd;
	unsigned int TimeSpend;
	TimeStart = clock();
	Sleep(100);
	TimeEnd = clock();

	TimeSpend = TimeEnd - TimeStart;

	CString TempCString;
	TempCString.Format(_T("ʱ����:%u����\r\n"),TimeSpend);
	this->Printf(TempCString);

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
	this->Printf(m_strTime);
	this->Printf((CString)"ʱ��������\r\n");

}

/*************************************************************************************/
//�ļ���������
void Example::FileOperation(void){
	this->Printf((CString)"�ļ��������Կ�ʼ\r\n");

	const char data[] = {"This is a test program"};
	CFile mFile(_T("../Output/Test.txt"),CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(data,sizeof(data));
	mFile.Close();

	this->Printf((CString)"�ļ������������\r\n");

}

/*************************************************************************************/
//����������
DWORD WINAPI ProcessTestThread(LPVOID pParam)
{
	Example *Ex = (Example *)pParam;
	Ex->Printf((CString)"�������������Կ�ʼ\r\n");
	for(int i=0;i<100;i++){
		Sleep(100);
		Ex->ProcessCtrl(i);
	}
	Ex->Printf((CString)"�������������Խ���\r\n");
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
	this->Printf((CString)"������ز��Կ�ʼ\r\n");
	CString IPCString;
	this->GetHostAddress(IPCString);
	IPCString = (CString)("����IP��ַ:")+ IPCString + (CString)("\r\n");
	this->Printf(IPCString);
	this->Printf((CString)"������ز��Խ���\r\n");
}
/*************************************************************************************/
//Windows CMD�����������
void Example::WinCMDTest(void){
	this->Printf((CString)"Windows CMD�������:ipconfig\r\n");
	WinExec("ipconfig", SW_HIDE);
}

void Example::OpencvFillRectangle(IplImage* img,UINT32 Startx,UINT32 Starty,UINT32 Endx,UINT32 Endy){
	CvPoint pt2[4] = {cvPoint(Startx,Starty),cvPoint(Endx,Starty),cvPoint(Endx,Endy),cvPoint(Startx,Endy)};
	cvFillConvexPoly(img,pt2,4,CV_RGB(0,0,0)); 
}

void Example::OpencvTest(void)
{
	IplImage *img = cvLoadImage("../Input/OpencvTest.jpg");
	cvNamedWindow("Opencv����",CV_WINDOW_AUTOSIZE);
	cvShowImage("Opencv����",img);

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
	cvShowImage("Opencv�Ի�ͼ",img2);

}