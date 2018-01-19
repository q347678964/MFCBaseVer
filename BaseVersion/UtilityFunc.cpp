#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "UtilityFunc.h"
#include "BaseVersionDlg.h"
#include "png.h"

/*************************************************************************************/
//���졢��������
UtilityFunc::UtilityFunc(){

}

UtilityFunc::~UtilityFunc(){

}
/*************************************************************************************/
//���������
void UtilityFunc::Init(void)
{
	g_PrintfSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
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

void UtilityFunc::PrintfToFile(CString Context){
	CTime time = CTime::GetCurrentTime();   ///����CTime����
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + (CString)("[UtilityFunc]") + Context;
    this->LogPrintf(Context);
}

void UtilityFunc::Printf(CString Context){
	CTime time = CTime::GetCurrentTime();   ///����CTime����
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + (CString)("[UtilityFunc]") + Context;
    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->Printf(Context);
}

CWnd* UtilityFunc::IDToCWnd(int HDCID)
{
	CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	HWND MainDlgHWND = (AfxGetMainWnd())->GetSafeHwnd(); //��ȡ����Cwnd,�ٻ�ȡHWND
	return MainDlg->FromHandle(GetDlgItem(MainDlgHWND,HDCID));	//��ȡ�ؼ���HWND,�ٴ���ΪCwnd���ڲ����ؼ�.
}

CWnd* UtilityFunc::GetDlgCWnd(void)
{
	return AfxGetMainWnd();
}

void UtilityFunc::ShowCwnd(CWnd *StaticCwnd,char *WinName)
{

	HDC StaticHDC = GetDC(*StaticCwnd);			//��ȡ�ؼ���CDC
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
