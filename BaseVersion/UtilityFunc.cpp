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
/*
*	IDToCWnd ���ݿؼ���ID�����ؿؼ��Ŀ��ƾ��Cwnd
*	@Parameters: HDCID(�ؼ�ID����IDC_BUTTON_1)
*	@Return: CWnd
*	@Author: Huaqing Yang
*/
CWnd* UtilityFunc::IDToCWnd(int HDCID)
{
	CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	HWND MainDlgHWND = (AfxGetMainWnd())->GetSafeHwnd(); //��ȡ����Cwnd,�ٻ�ȡHWND
	return MainDlg->FromHandle(GetDlgItem(MainDlgHWND,HDCID));	//��ȡ�ؼ���HWND,�ٴ���ΪCwnd���ڲ����ؼ�.
}
/*
*	GetDlgCWnd ���ص�ǰMain����Cwnd
*	@Parameters: Void
*	@Return: CWnd
*	@Author: Huaqing Yang
*/
CWnd* UtilityFunc::GetDlgCWnd(void)
{
	return AfxGetMainWnd();
}

/*
*	CwndToCRect ��ȡCwnd����Ĵ�С
*	@Parameters: StaticCwnd��rect
*	@Return: Void
*	@Author: Huaqing Yang
*/
void UtilityFunc::CwndToCRect(CWnd *StaticCwnd,CRect *rect)
{
	HDC StaticHDC = GetDC(*StaticCwnd);			//��ȡ�ؼ���CDC
	CDC *StaticCDC = CDC::FromHandle(StaticHDC);//HDC->CDC
	if(StaticCDC != NULL){
		StaticCwnd->GetWindowRect(rect);
	}
	return;
}

/*
*	SetIplImagePixel ����Iplimageͼ��ָ�����������ֵ��֧���κ�Channels��.
*	@Parameters: img, x��y��Pixel
*	@Return: Void
*	@Author: Huaqing Yang
*/
void UtilityFunc::SetIplImagePixel(IplImage *img,int x,int y,unsigned char *Pixel){
	uchar* ImageData=(uchar *)img->imageData; 
	int ImageWidth = img->width;
	int ImageHeight = img->height;
	int nchannels = img->nChannels;
	for(int i=0;i<nchannels;i++)
		ImageData[y*ImageWidth*nchannels+x*nchannels+i] = Pixel[i];
}
/*
*	GetIplImagePixel ��ȡIplimageͼ��ָ�����������ֵ��֧���κ�Channels��.
*	@Parameters: img, x��y��Pixel
*	@Return: Void
*	@Author: Huaqing Yang
*/
void UtilityFunc::GetIplImagePixel(IplImage *img,int x,int y,unsigned char *Pixel){
	uchar* ImageData=(uchar *)img->imageData; 
	int ImageWidth = img->width;
	int ImageHeight = img->height;
	int nchannels = img->nChannels;
	for(int i=0;i<nchannels;i++)
		Pixel[i] = ImageData[y*ImageWidth*nchannels+x*nchannels+i];
}


/*
*	PixelCompared �Ƚ�������ɫ����
*	@Parameters: Pixel1, Pixel2
*	@Return 1:���ƣ�-1:������
*	@Author: Huaqing Yang
*/
#define PIXEL_COMPARED_LEVEL 20
int UtilityFunc::PixelCompared(unsigned char *Pixel1,unsigned char *Pixel2){
	int Level;
	for(int i=0;i<3;i++){
		Level = Pixel1[i]>Pixel2[i]?Pixel1[i]-Pixel2[i]:Pixel2[i]-Pixel1[i];
		if(Level < PIXEL_COMPARED_LEVEL){
			return 1;
		}else{
			return -1;
		}
	}
}

/*
*	HSVCompared �Ƚ�HSV������ɫ����
*	@Parameters: SrcH, SrcS,SrcV,DestH,DestS,DestV,DIFF
*	@DIFF �����
*	@Return 1:���ƣ�-1:������
*	@Author: Huaqing Yang
*	Opencv H (0~255) S(0~180) V(0~180)
*	����	H (0~180) S(0~1) V(0~1)
*/
int UtilityFunc::HSVCompared(unsigned char SrcH,unsigned char SrcS,unsigned char SrcV,unsigned char DestH,unsigned char DestS,unsigned char DestV,unsigned char DIFF){
	int HDiff = SrcH>DestH?SrcH-DestH:DestH-SrcH;
	int SDiff = SrcS>DestS?SrcS-DestS:DestS-SrcS;
	int VDiff = SrcV>DestV?SrcV-DestV:DestV-SrcV;

	if(HDiff < DIFF &&SDiff < DIFF && VDiff < DIFF){
		return 1;
	}else{
		return -1;
	}
}
/*
*	RGBToHSV RGBͼ��ת��Ϊ��ʱHSVͼ���ٷ����H,S,Vͼ��ͼ����Ҫ��������Create
*	@Parameters: SrcImage, HImage,SImage,VImage
*	@Return: Void
*	@Author: Huaqing Yang
*/
void UtilityFunc::RGBToHSV(IplImage *SrcImage,IplImage *HImage,IplImage *SImage,IplImage *VImage){
	int ImageWidth = SrcImage->width;
	int ImageHeight = SrcImage->height;
	int Nchannels = SrcImage->nChannels;
	IplImage *HSVImage = cvCreateImage(cvGetSize(SrcImage),IPL_DEPTH_8U,Nchannels);

	cvCvtColor(SrcImage,HSVImage,CV_BGR2HSV);

	cvSplit(HSVImage,HImage,SImage,VImage,0);

	cvReleaseImage(&HSVImage);
}
/*
*	CwndToIplImage ��Cwnd���ڵ�HDC(UI)����ת����IplImageͼ��
*	@Parameters: StaticCwnd, DestImage
*	@Return: Void
*	@Author: Huaqing Yang
*/
void UtilityFunc::CwndToIplImage(CWnd *StaticCwnd,IplImage *DestImage)
{
	HDC StaticHDC = GetDC(*StaticCwnd);			//��ȡ�ؼ���CDC
	CDC *StaticCDC = CDC::FromHandle(StaticHDC);//HDC->CDC
	FormatChange FC;
	if(StaticCDC != NULL){
		CRect StaticRect;
		StaticCwnd->GetWindowRect(&StaticRect);
		int StaticWidth = StaticRect.Width();
		int StaticHeight = StaticRect.Height();

		if(StaticWidth>1 && StaticHeight>1){

			uchar* ImageData=(uchar *)DestImage->imageData; 
			int channels = DestImage->nChannels;  
			
			CBitmap SaveCBitmap;
			HBITMAP SaveHbitmap;
			SaveCBitmap.CreateCompatibleBitmap(StaticCDC,StaticWidth,StaticHeight); 
			CDC MemCDC;
			MemCDC.CreateCompatibleDC(StaticCDC);
			MemCDC.SelectObject(SaveCBitmap);	//ѡ��Ŀ��֮������ڴ�λ�ã�
			MemCDC.BitBlt(0,0,StaticWidth,StaticHeight,StaticCDC,0,0,SRCCOPY);//����Ŀ��CDC���ڴ�CDC�У������ٴ�CBitmap��������

			unsigned char *HDCData = (unsigned char *) malloc(StaticWidth*StaticHeight*4);
			SaveCBitmap.GetBitmapBits(StaticWidth*StaticHeight*4,HDCData);

			for(int i=0;i<StaticHeight;i++){
				for(int j=0;j<StaticWidth;j++){
					//Opencv -> BGR, CBitmap -> BGR
					ImageData[i*StaticWidth*channels+j*channels+0] = HDCData[i*StaticWidth*4+j*4+0];
					ImageData[i*StaticWidth*channels+j*channels+1] = HDCData[i*StaticWidth*4+j*4+1];
					ImageData[i*StaticWidth*channels+j*channels+2] = HDCData[i*StaticWidth*4+j*4+2];
				}
			}

			free(HDCData);
			

		}
	}

}
/*
*	ShowCwnd ��ʾCwnd���ڵ�HDC(UI)����,���ұ��浽../Output/Image.jpg
*	@Parameters: StaticCwnd, WinName
*	@Return: Void
*	@Author: Huaqing Yang
*/
void UtilityFunc::ShowCwnd(CWnd *StaticCwnd,char *WinName)
{

	HDC StaticHDC = GetDC(*StaticCwnd);			//��ȡ�ؼ���CDC
	CDC *StaticCDC = CDC::FromHandle(StaticHDC);//HDC->CDC
	FormatChange FC;
	if(StaticCDC != NULL){
		CRect StaticRect;
		StaticCwnd->GetWindowRect(&StaticRect);
		int StaticWidth = StaticRect.Width();
		int StaticHeight = StaticRect.Height();

		if(StaticWidth>1 && StaticHeight>1){
			IplImage *img = cvCreateImage(cvSize(StaticWidth,StaticHeight),8,3);
			uchar* ImageData=(uchar *)img->imageData; 
			int channels = img->nChannels;  
			
			CBitmap SaveCBitmap;
			HBITMAP SaveHbitmap;
			SaveCBitmap.CreateCompatibleBitmap(StaticCDC,StaticWidth,StaticHeight); 
			CDC MemCDC;
			MemCDC.CreateCompatibleDC(StaticCDC);
			MemCDC.SelectObject(SaveCBitmap);	//ѡ��Ŀ��֮������ڴ�λ�ã�
			MemCDC.BitBlt(0,0,StaticWidth,StaticHeight,StaticCDC,0,0,SRCCOPY);//����Ŀ��CDC���ڴ�CDC�У������ٴ�CBitmap��������

			unsigned char *HDCData = (unsigned char *) malloc(StaticWidth*StaticHeight*4);
			SaveCBitmap.GetBitmapBits(StaticWidth*StaticHeight*4,HDCData);

			for(int i=0;i<StaticHeight;i++){
				for(int j=0;j<StaticWidth;j++){
					//Opencv -> BGR, CBitmap -> BGR
					ImageData[i*StaticWidth*channels+j*channels+0] = HDCData[i*StaticWidth*4+j*4+0];
					ImageData[i*StaticWidth*channels+j*channels+1] = HDCData[i*StaticWidth*4+j*4+1];
					ImageData[i*StaticWidth*channels+j*channels+2] = HDCData[i*StaticWidth*4+j*4+2];
				}
			}

			free(HDCData);
			cvNamedWindow(WinName,CV_WINDOW_AUTOSIZE);
			cvShowImage(WinName,img);
			cvSaveImage("../Output/Image.jpg",img);
		}
	}

	
}


/*
*	XSleep ��������ʱ�����Sleep���ù��ܿ����ͷ�CPU���÷���Sleepһ��
*	@Parameters: nWaitInMsecs
*	@Return: Void
*	@Author: Huaqing Yang
*/
struct XSleep_Structure   
{  
    int duration;  
    HANDLE evenHandle;  
};  
  
DWORD WINAPI XSleepThread(LPVOID pWaitTime)  
{  
    XSleep_Structure *sleep = (XSleep_Structure*)pWaitTime;  
  
  
    Sleep(sleep->duration);  
    SetEvent(sleep->evenHandle);  
  
  
    return 0;  
}  

void UtilityFunc::XSleep(int nWaitInMsecs)  
{  
    XSleep_Structure sleep;  
    sleep.duration = nWaitInMsecs;  
    sleep.evenHandle = CreateEvent(NULL,TRUE,FALSE,NULL);  
      
    DWORD dwThreadId;  
    CreateThread(NULL,0,&XSleepThread,&sleep,0,&dwThreadId);  
  
    MSG msg;  
    while(::WaitForSingleObject(sleep.evenHandle,0) == WAIT_TIMEOUT)  
    {  
        // get and dispatch message  
        if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE))  
        {  
            ::TranslateMessage(&msg);  
            ::DispatchMessage(&msg);  
        }  
    }  
    CloseHandle(sleep.evenHandle);  
}  