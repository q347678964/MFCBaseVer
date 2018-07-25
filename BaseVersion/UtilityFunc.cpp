#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "UtilityFunc.h"
#include "BaseVersionDlg.h"
#include "png.h"

/*************************************************************************************/
//构造、析构函数
UtilityFunc::UtilityFunc(){
	g_PrintfSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
}

UtilityFunc::~UtilityFunc(){

}
/*************************************************************************************/
//主窗体操作
void UtilityFunc::Init(void)
{
	
}
void UtilityFunc::Exit(void)
{
}
void UtilityFunc::LogPrintf(CString Context){
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

void UtilityFunc::PrintfCStringToFile(CString Context){
	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + Context;
    this->LogPrintf(Context);
}

void UtilityFunc::PrintfCString(CString Context){
	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + Context;
    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->Printf(Context);
}

void UtilityFunc::Printf(const char*pFmg, ...){
	va_list Args;
	char TempBuff[1024];

    va_start(Args, pFmg);
	vsprintf(TempBuff,pFmg,Args);
	CString PrintCString;

	PrintCString.Format(CString(TempBuff));
	this->PrintfCString(PrintCString);
    va_end(Args);
}

void UtilityFunc::PrintfFile(char*pFmg, ...){
	va_list Args;
	char TempBuff[1024];

    va_start(Args, pFmg);
	vsprintf(TempBuff,pFmg,Args);
	CString PrintCString;

	PrintCString.Format(CString(TempBuff));
	this->PrintfCStringToFile(PrintCString);
    va_end(Args);
}

CWnd* UtilityFunc::IDToCWnd(int HDCID)
{
	CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	HWND MainDlgHWND = (AfxGetMainWnd())->GetSafeHwnd(); //获取窗口Cwnd,再获取HWND
	return MainDlg->FromHandle(GetDlgItem(MainDlgHWND,HDCID));	//获取控件的HWND,再传唤为Cwnd用于操作控件.
}

CWnd* UtilityFunc::GetDlgCWnd(void)
{
	return AfxGetMainWnd();
}

void UtilityFunc::ShowCwnd(CWnd *StaticCwnd,char *WinName)
{

	HDC StaticHDC = GetDC(*StaticCwnd);			//获取控件的CDC
	CDC *StaticCDC = CDC::FromHandle(StaticHDC);//HDC->CDC

	if(StaticCDC != NULL){
		CRect StaticRect;
		StaticCwnd->GetWindowRect(&StaticRect);
		int StaticWidth = StaticRect.Width();
		int StaticHeight = StaticRect.Height();
		if(StaticWidth>1 && StaticHeight>1){
			IplImage *img2 = cvCreateImage(cvSize(StaticWidth,StaticHeight),8,3);

			for(int i=0;i<StaticWidth;i++){
				for(int j=0;j<StaticHeight;j++){
					COLORREF Col = StaticCDC->GetPixel(i,j);
					
					unsigned char PixelR = GetRValue(Col);
					unsigned char PixelG = GetGValue(Col);
					unsigned char PixelB = GetBValue(Col);

					CvPoint centerpoint;
					centerpoint.x=i;
					centerpoint.y=j;
					cvCircle(img2, centerpoint ,3 , CV_RGB(PixelR,PixelG,PixelB),1, 8, 3 );

				}
			}

			cvNamedWindow(WinName,CV_WINDOW_AUTOSIZE);
			cvShowImage(WinName,img2);
		}
	}
}
